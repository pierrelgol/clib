const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const clib = b.addStaticLibrary(.{
        .name = "clib",
        .target = target,
        .optimize = optimize,
    });
    clib.linkLibC();
    clib.addIncludePath(.{ .path = "include/" });
    for (c_source_files) |path| {
        clib.addCSourceFile(.{ .file = .{ .path = path }, .flags = &.{
            "-Wall",
            "-Wextra",
            "-Werror",
        } });
    }
    b.installArtifact(clib);

    const main_tests = b.addTest(.{
        .root_source_file = .{ .path = "testing/unit_test/test.zig" },
        .target = target,
        .optimize = optimize,
    });
    main_tests.addIncludePath(.{ .path = "include/" });
    main_tests.linkLibrary(clib);
    main_tests.linkLibC();

    const run_main_tests = b.addRunArtifact(main_tests);
    const test_step = b.step("test", "Run library tests");
    test_step.dependOn(&run_main_tests.step);
}

const c_source_files = [_][]const u8{
    "source/allocator/arena_allocator_alloc.c",
    "source/allocator/arena_allocator_dealloc.c",
    "source/allocator/arena_allocator_deinit.c",
    "source/allocator/arena_allocator_init.c",
    "source/allocator/arena_allocator_realloc.c",
    "source/allocator/arena_allocator_reserve.c",
    "source/allocator/heap_alloc.c",
    "source/allocator/heap_dealloc.c",
    "source/allocator/heap_deinit.c",
    "source/allocator/heap_init.c",
    "source/allocator/heap_realloc.c",
    "source/allocator/heap_reserve.c",
    "source/allocator/logging_allocator_alloc.c",
    "source/allocator/logging_allocator_dealloc.c",
    "source/allocator/logging_allocator_deinit.c",
    "source/allocator/logging_allocator_init.c",
    "source/allocator/logging_allocator_realloc.c",
    "source/allocator/logging_allocator_reserve.c",
    "source/char/char_is_alnum.c",
    "source/char/char_is_alpha.c",
    "source/char/char_is_ascii.c",
    "source/char/char_is_binary.c",
    "source/char/char_is_decimal.c",
    "source/char/char_is_digit.c",
    "source/char/char_is_even.c",
    "source/char/char_is_hex.c",
    "source/char/char_is_lowercase.c",
    "source/char/char_is_newline.c",
    "source/char/char_is_octal.c",
    "source/char/char_is_odd.c",
    "source/char/char_is_printable.c",
    "source/char/char_is_spaces.c",
    "source/char/char_is_uppercase.c",
    "source/char/char_is_whitespace.c",
    "source/char/char_to_lowercase.c",
    "source/char/char_to_reversecase.c",
    "source/char/char_to_uppercase.c",
    "source/list/list_clear.c",
    "source/list/list_clone.c",
    "source/list/list_concat.c",
    "source/list/list_create.c",
    "source/list/list_destroy.c",
    "source/list/list_insert_at.c",
    "source/list/list_length.c",
    "source/list/list_peek_at.c",
    "source/list/list_pop_at.c",
    "source/list/list_push_at.c",
    "source/list/list_remove_at.c",
    "source/list/list_rotate.c",
    "source/list/list_sort.c",
    "source/list/list_split_at.c",
    "source/memory/memory_alloc.c",
    "source/memory/memory_ccopy.c",
    "source/memory/memory_compare.c",
    "source/memory/memory_copy.c",
    "source/memory/memory_dealloc.c",
    "source/memory/memory_dup.c",
    "source/memory/memory_dupz.c",
    "source/memory/memory_move.c",
    "source/memory/memory_realloc.c",
    "source/memory/memory_search.c",
    "source/memory/memory_set.c",
    "source/memory/memory_zalloc.c",
    "source/string/string_bsearch.c",
    "source/string/string_casecompare.c",
    "source/string/string_clone.c",
    "source/string/string_compare.c",
    "source/string/string_concat.c",
    "source/string/string_copy.c",
    "source/string/string_count.c",
    "source/string/string_count_token.c",
    "source/string/string_count_leading.c",
    "source/string/string_count_trailing.c",
    "source/string/string_count_until.c",
    "source/string/string_cspan.c",
    "source/string/string_join.c",
    "source/string/string_lconcat.c",
    "source/string/string_lcopy.c",
    "source/string/string_length.c",
    "source/string/string_ncasecompare.c",
    "source/string/string_nclone.c",
    "source/string/string_ncompare.c",
    "source/string/string_nconcat.c",
    "source/string/string_ncopy.c",
    "source/string/string_next_token.c",
    "source/string/string_rbsearch.c",
    "source/string/string_reverse.c",
    "source/string/string_search.c",
    "source/string/string_span.c",
    "source/string/string_split.c",
    "source/string/string_split_destroy.c",
    "source/string/string_substring.c",
    "source/string/string_tokenize.c",
    "source/string/string_tolower.c",
    "source/string/string_toupper.c",
};
