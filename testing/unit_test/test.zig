const std = @import("std");
const mem = std.mem;
const debug = std.debug;
const testing = std.testing;
const process = std.process;
const log = std.log;
const c = std.c;
const ascii = std.ascii;
const bind = @import("bindings.zig");

const HeapAllocator = bind.HeapAllocator;
const ArenaAllocator = bind.ArenaAllocator;
const Cresult = bind.CResult;

const logInfo = log.info;
const logWarn = log.warn;
const logErr = log.err;
const expectTrue = testing.expect;
const expectEqual = testing.expectEqual;
const expectError = testing.expectError;
const expectFmt = testing.expectFmt;
const expectEqualSlice = testing.expectEqualSlices;
const expectEqualString = testing.expectEqualStrings;
const expectStringStartsWith = testing.expectStringStartsWith;
const expectStringEndsWith = testing.expectStringEndsWith;

const sliceFromAnyopaque = bind.sliceFromAnyopaque;
const sliceFromCstr = bind.sliceFromCstr;
const anyopaqueFromSlice = bind.anyopaqueFromSlice;
const cstrFromSlice = bind.cstrFromSlice;

// ***********************************+************************************** //
//                                 Char                                       //
// ************************************************************************** //

test "char_is_alnum : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charIsAlnum(character);
        switch (index) {
            'A'...'Z', 'a'...'z', '0'...'9' => try expectTrue(result == true),
            else => try expectTrue(result == false),
        }
    }
}

test "char_is_alpha : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charIsAlpha(character);
        switch (index) {
            'A'...'Z', 'a'...'z' => try expectTrue(result == true),
            else => try expectTrue(result == false),
        }
    }
}

test "char_is_ascii : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charIsAscii(character);
        switch (index) {
            0...127 => try expectTrue(result == true),
            else => try expectTrue(result == false),
        }
    }
}

test "char_is_binary : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charIsBinary(character);
        switch (index) {
            '0'...'1' => try expectTrue(result == true),
            else => try expectTrue(result == false),
        }
    }
}

test "char_is_decimal : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charIsDecimal(character);
        switch (index) {
            '0'...'9', '.' => try expectTrue(result == true),
            else => try expectTrue(result == false),
        }
    }
}

test "char_is_digit : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charIsDigit(character);
        switch (index) {
            '0'...'9' => try expectTrue(result == true),
            else => try expectTrue(result == false),
        }
    }
}

test "char_is_even : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charIsEven(character);
        switch (index % 2) {
            0 => try expectTrue(result == true),
            else => try expectTrue(result == false),
        }
    }
}

test "char_is_hex : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charIsHex(character);
        switch (index) {
            'A'...'F', 'a'...'f', '0'...'9' => try expectTrue(result == true),
            else => try expectTrue(result == false),
        }
    }
}

test "char_is_lowercase : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charIsLowercase(character);
        switch (index) {
            'a'...'z' => try expectTrue(result == true),
            else => try expectTrue(result == false),
        }
    }
}
test "char_is_uppercase : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charIsUppercase(character);
        switch (index) {
            'A'...'Z' => try expectTrue(result == true),
            else => try expectTrue(result == false),
        }
    }
}

test "char_is_newline : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charIsNewline(character);
        switch (index) {
            '\n' => try expectTrue(result == true),
            else => try expectTrue(result == false),
        }
    }
}

test "char_is_octal : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charIsOctal(character);
        switch (index) {
            '0'...'7' => try expectTrue(result == true),
            else => try expectTrue(result == false),
        }
    }
}

test "char_is_odd : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charIsOdd(character);
        switch (index % 2) {
            0 => try expectTrue(result == false),
            else => try expectTrue(result == true),
        }
    }
}

test "char_is_printable : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charIsPrintable(character);
        switch (index) {
            32...126 => try expectTrue(result == true),
            else => try expectTrue(result == false),
        }
    }
}

test "char_is_spaces : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charIsSpaces(character);
        switch (index) {
            9...13, 32 => try expectTrue(result == true),
            else => try expectTrue(result == false),
        }
    }
}

test "char_is_whitespace : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charIsWhitespace(character);
        switch (index) {
            ascii.control_code.vt => try expectTrue(result == true),
            ascii.control_code.ht => try expectTrue(result == true),
            ' ' => try expectTrue(result == true),
            else => try expectTrue(result == false),
        }
    }
}

test "char_to_lowercase : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charToLowercase(character);
        switch (index) {
            'A'...'Z' => try expectTrue(result == (character + 32)),
            else => try expectTrue(result == character),
        }
    }
}

test "char_to_uppercase : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charToUppercase(character);
        switch (index) {
            'a'...'z' => try expectTrue(result == (character - 32)),
            else => try expectTrue(result == character),
        }
    }
}

test "char_to_reversecase : test1" {
    for (0..255) |index| {
        const character: u8 = @truncate(index);
        const result = bind.charToReversecase(character);
        switch (index) {
            'a'...'z' => try expectTrue(result == (character - 32)),
            'A'...'Z' => try expectTrue(result == (character + 32)),
            else => try expectTrue(result == character),
        }
    }
}

// ***********************************+************************************** //
//                                 String                                     //
// ************************************************************************** //

test "string_bsearch : test1" {
    const result = try bind.stringBsearch("This is a string", 'g');
    try expectTrue(result[0] == 'g');
}

test "string_bsearch : test2" {
    try expectError(Cresult.NotFound, bind.stringBsearch("This is a test", 'c'));
}

test "string_bsearch : test3" {
    try expectEqualString("", try bind.stringBsearch("", 'g'));
}

// ***********************************+************************************** //

test "string_casecompare : test1" {
    try expectTrue(bind.stringCasecompare("This is a test", "This is a test") == 0);
}

test "string_casecompare : test2" {
    try expectTrue(bind.stringCasecompare("THIS IS A TEST", "THIS IS A TEST") == 0);
}

test "string_casecompare : test3" {
    try expectTrue(bind.stringCasecompare("THIS IS A TEST", "this is a test") == 0);
}

test "string_casecompare : test4" {
    try expectTrue(bind.stringCasecompare("this is a test", "THIS IS A TEST") == 0);
}

// ***********************************+************************************** //

test "string_clone : test1" {
    const allocator = bind.ClibHeapAllocator().init();
    defer allocator.deinit();
    const str = bind.stringClone(allocator.allocator, "This is a test");
    defer allocator.dealloc(str);
    try expectEqualString(str, "This is a test");
}

test "string_clone : test2" {
    const allocator = bind.ClibHeapAllocator().init();
    defer allocator.deinit();

    const str = bind.stringClone(allocator.allocator, "a");
    defer allocator.dealloc(str);
    try expectEqualString(str, "a");
}

test "string_clone : test3" {
    const allocator = bind.ClibHeapAllocator().init();
    defer allocator.deinit();

    const str = bind.stringClone(allocator.allocator, "");
    defer allocator.dealloc(str);
    try expectEqualString(str, "");
}

// ***********************************+************************************** //

test "string_compare : test1" {
    const str1 = bind.memoryDupz("This is a string", bind.stringLength("This is a string"));
    defer bind.memoryDealloc(str1);

    const str2 = bind.memoryDupz("This is a string", bind.stringLength("This is a string"));
    defer bind.memoryDealloc(str2);

    try expectEqualString(str1, str2);
    try expectTrue(bind.stringCompare(str1, str2) == 0);
}

test "string_compare : test2" {
    const str1 = bind.memoryDupz("This is a stringa", bind.stringLength("This is a stringa"));
    defer bind.memoryDealloc(str1);

    const str2 = bind.memoryDupz("This is a stringb", bind.stringLength("This is a stringb"));
    defer bind.memoryDealloc(str2);

    try expectTrue(bind.stringCompare(str1, str2) == -1);
}

test "string_compare : test3" {
    const str1 = bind.memoryDupz("This is a stringb", bind.stringLength("This is a stringb"));
    defer bind.memoryDealloc(str1);

    const str2 = bind.memoryDupz("This is a stringa", bind.stringLength("This is a stringa"));
    defer bind.memoryDealloc(str2);

    try expectTrue(bind.stringCompare(str1, str2) == 1);
}

// ***********************************+************************************** //

test "string_concat : test1" {
    const str = bind.memoryZalloc(bind.stringLength("Hello, World!"));
    defer bind.memoryDealloc(str);

    _ = bind.stringConcat(str, "Hello, ");
    _ = bind.stringConcat(str, "World!");
    try expectEqualString(str, "Hello, World!");
}

test "string_concat : test2" {
    const str = bind.memoryZalloc(bind.stringLength("World!"));
    defer bind.memoryDealloc(str);

    _ = bind.stringConcat(str, "");
    _ = bind.stringConcat(str, "World!");
    try expectEqualString(str, "World!");
}

test "string_concat : test3" {
    const str = bind.memoryZalloc(bind.stringLength("Hello!"));
    defer bind.memoryDealloc(str);

    _ = bind.stringConcat(str, "Hello!");
    _ = bind.stringConcat(str, "");
    try expectEqualString(str, "Hello!");
}

// ***********************************+************************************** //

test "string_copy : test1" {
    const str = bind.memoryZalloc(14);
    defer bind.memoryDealloc(str);
    _ = bind.stringCopy(str, "This is a test");
    try expectEqualString(str, "This is a test");
}

test "string_copy : test2" {
    const str = bind.memoryZalloc(1);
    defer bind.memoryDealloc(str);
    _ = bind.stringCopy(str, "T");
    try expectEqualString(str, "T");
}

test "string_copy : test3" {
    const str = bind.memoryZalloc(0);
    defer bind.memoryDealloc(str);
    _ = bind.stringCopy(str, "");
    try expectEqualString(str, "");
}

// ***********************************+************************************** //

test "string_count : test1" {
    const result = bind.stringCount("This is a string", ' ');
    try expectTrue(result == 3);
}

test "string_count : test2" {
    const result = bind.stringCount("This is a string", 'z');
    try expectTrue(result == 0);
}

test "string_count : test3" {
    const result = bind.stringCount("", ' ');
    try expectTrue(result == 0);
}

// ***********************************+************************************** //

test "string_cspan : test1" {
    const result = bind.stringCspan("This is a string", " ");
    try expectTrue(result == 4);
}

test "string_cspan : test2" {
    const result = bind.stringCspan("This is a string", "z");
    try expectTrue(result == 16);
}

test "string_cspan : test3" {
    const result = bind.stringCspan("This is a string", "T");
    try expectTrue(result == 0);
}

// ***********************************+************************************** //

test "string_count_leading : test1" {
    const str1 = "aaa_bbb_ccc";
    const result = bind.stringCountLeading(str1, 'a');
    try expectTrue(result == 3);
}

test "string_count_leading : test2" {
    const str1 = "aaa_bbb_ccc";
    const result = bind.stringCountLeading(str1, 'b');
    try expectTrue(result == 0);
}

test "string_count_leading : test3" {
    const str1 = "aaa_bbb_ccc";
    const result = bind.stringCountLeading(str1, 'c');
    try expectTrue(result == 0);
}

test "string_count_leading : test4" {
    const str1 = "aaa_bbb_ccc";
    const result = bind.stringCountLeading(str1, 'z');
    try expectTrue(result == 0);
}

test "string_count_leading : test5" {
    const str1 = "aaa" ** 10;
    const result = bind.stringCountLeading(str1, 'a');
    try expectTrue(result == 30);
}

// ***********************************+************************************** //

test "string_count_trailing : test1" {
    const str1 = "aaa_bbb_ccc";
    const result = bind.stringCountTrailing(str1, 'a');
    try expectTrue(result == 0);
}

test "string_count_trailing : test2" {
    const str1 = "aaa_bbb_ccc";
    const result = bind.stringCountTrailing(str1, 'b');
    try expectTrue(result == 0);
}

test "string_count_trailing : test3" {
    const str1 = "aaa_bbb_ccc";
    const result = bind.stringCountTrailing(str1, 'c');
    try expectTrue(result == 3);
}

test "string_count_trailing : test4" {
    const str1 = "aaa_bbb_ccc";
    const result = bind.stringCountTrailing(str1, 'z');
    try expectTrue(result == 0);
}

test "string_count_trailing : test5" {
    const str1 = "aaa" ** 10;
    const result = bind.stringCountTrailing(str1, 'a');
    try expectTrue(result == 30);
}

// ***********************************+************************************** //

test "string_count_until : test1" {
    const str1 = "aaa_bbb_ccc";
    const result = bind.stringCountUntil(str1, 'a');
    try expectTrue(result == 0);
}

test "string_count_until : test2" {
    const str1 = "aaa_bbb_ccc";
    const result = bind.stringCountUntil(str1, 'b');
    try expectTrue(result == 4);
}

test "string_count_until : test3" {
    const str1 = "aaa_bbb_ccc";
    const result = bind.stringCountUntil(str1, 'c');
    try expectTrue(result == 8);
}

test "string_count_until : test4" {
    const str1 = "aaa_bbb_ccc";
    const result = bind.stringCountUntil(str1, 'z');
    try expectTrue(result == str1.len);
}

test "string_count_until : test5" {
    const str1 = "aaa" ** 10;
    const result = bind.stringCountUntil(str1, 'a');
    try expectTrue(result == 0);
}

// ***********************************+************************************** //

test "string_count_token : test1" {
    const str = "This is a very long string with a lot of words";
    const delim = " ";
    const result = bind.stringCountToken(str, delim);
    try expectTrue(result == 11);
}

test "string_count_token : test2" {
    const str = "This is a very long string with a lot of words";
    const delim = "z";
    const result = bind.stringCountToken(str, delim);
    try expectTrue(result == 1);
}

test "string_count_token : test3" {
    const str = "";
    const delim = "z";
    const result = bind.stringCountToken(str, delim);
    try expectTrue(result == 0);
}

test "string_count_token : test4" {
    const str = "This is a very long string with a lot of words";
    const delim = "abcdefhijklmnopqrstuvwxyz";
    const result = bind.stringCountToken(str, delim);
    try expectTrue(result == 11);
}

test "string_count_token : test5" {
    const str = "   This   is  a   very long     string with a lot of words  ";
    const delim = " ";
    const result = bind.stringCountToken(str, delim);
    try expectTrue(result == 11);
}

// ***********************************+************************************** //

test "string_join : test1" {
    const heap = bind.ClibHeapAllocator().init();
    defer heap.deinit();

    const result = bind.stringJoin(heap.allocator, "Hello, ", "World!");
    defer heap.dealloc(result);
    try expectEqualString(result, "Hello, World!");
}

test "string_join : test2" {
    const heap = bind.ClibHeapAllocator().init();
    defer heap.deinit();

    const result = bind.stringJoin(heap.allocator, "", "World!");
    defer heap.dealloc(result);
    try expectEqualString(result, "World!");
}

test "string_join : test3" {
    const heap = bind.ClibHeapAllocator().init();
    defer heap.deinit();

    const result = bind.stringJoin(heap.allocator, "Hello", "");
    defer heap.dealloc(result);
    try expectEqualString(result, "Hello");
}

test "string_join : test4" {
    const heap = bind.ClibHeapAllocator().init();
    defer heap.deinit();

    const result = bind.stringJoin(heap.allocator, "", "");
    defer heap.dealloc(result);
    try expectEqualString(result, "");
}

// ***********************************+************************************** //

test "string_lconcat : test1" {
    const result = bind.clib.string_lconcat(null, null, 0);
    try expectTrue(result == 0);
}

test "string_lconcat : test2" {
    const result = bind.clib.string_lconcat(null, @ptrCast("This is a string"), 0);
    try expectTrue(result == 0);
}

test "string_lconcat : test3" {
    const result = bind.clib.string_lconcat(@constCast(@ptrCast("This is a string")), null, 0);
    try expectTrue(result == 0);
}

test "string_lconcat : test4" {
    const result = bind.stringLconcat("This is a string", " and this is the rest", 0);
    try expectTrue(result == bind.stringLength(" and this is the rest"));
}

test "string_lconcat : test5" {
    const result = bind.stringLconcat("This is a string", "1", 10);
    try expectTrue(result == 11);
}

test "string_lconcat : test6" {
    const result = bind.stringLconcat("This is a string", "1", 10);
    try expectTrue(result == 11);
}

test "string_lconcat : test7" {
    const str1 = bind.memoryZalloc(64);
    defer bind.memoryDealloc(str1);
    const result = bind.stringLconcat(str1, "This is a string", 64);
    try expectTrue(result == 16);
}

test "string_lconcat : test8" {
    const str1 = bind.memoryZalloc(12);
    defer bind.memoryDealloc(str1);
    const result = bind.stringLconcat(str1, "This is a string", 12);
    try expectTrue(result == 16);
    try expectStringStartsWith(str1, "This is a s");
}

// ***********************************+************************************** //

test "string_lcopy : test1" {
    const result = bind.stringLcopy("Hello", "This is a string", 0);
    try expectTrue(result == 16);
}

test "string_lcopy : test2" {
    const buffer = bind.memoryZalloc(16);
    defer bind.memoryDealloc(buffer);

    const result = bind.stringLcopy(buffer, "This is a string", 0);
    try expectTrue(result == 16);
}

test "string_lcopy : test3" {
    const buffer = bind.memoryZalloc(17);
    defer bind.memoryDealloc(buffer);

    const result = bind.stringLcopy(buffer, "This is a string", 17);
    try expectStringStartsWith(buffer, "This is a string");
    try expectTrue(result == 16);
}

// ***********************************+************************************** //

test "string_length : test1" {
    const str = "This is a test";
    try expectTrue(str.len == bind.stringLength(str));
}

test "string_length : test2" {
    const str = "T";
    try expectTrue(str.len == bind.stringLength(str));
}

test "string_length : test3" {
    const str = "abcdefhijklmnopqrstuvwxyz" ** 1000;
    try expectTrue(str.len == bind.stringLength(str));
}

test "string_length : test4" {
    const str = "";
    try expectTrue(str.len == bind.stringLength(str));
}

// ***********************************+************************************** //

test "string_ncasecompare : test1" {
    try expectTrue(bind.stringNcasecompare("This is a test", "This is a test", 16) == 0);
}

test "string_ncasecompare : test2" {
    try expectTrue(bind.stringNcasecompare("THIS IS A TEST", "THIS IS A TEST", 16) == 0);
}

test "string_ncasecompare : test3" {
    try expectTrue(bind.stringNcasecompare("this is a test", "this is a test", 16) == 0);
}

test "string_ncasecompare : test4" {
    try expectTrue(bind.stringNcasecompare("THIS IS A TEST", "this is a test", 16) == 0);
}

// ***********************************+************************************** //

test "string_nclone : test1" {
    const source = "This is a test";
    const allocator = bind.ClibHeapAllocator().init();
    defer allocator.deinit();
    const str = bind.stringNclone(allocator.allocator, source, source.len);
    defer allocator.dealloc(str);
    try expectEqualString(str, "This is a test");
}

test "string_nclone : test2" {
    const source = "a";
    const allocator = bind.ClibHeapAllocator().init();
    defer allocator.deinit();
    const str = bind.stringNclone(allocator.allocator, source, source.len);
    defer allocator.dealloc(str);
    try expectEqualString(str, "a");
}

test "string_nclone : test3" {
    const source = "";
    const allocator = bind.ClibHeapAllocator().init();
    defer allocator.deinit();
    const str = bind.stringNclone(allocator.allocator, source, source.len);
    defer allocator.dealloc(str);
    try expectEqualString(str, "");
}

// ***********************************+************************************** //

test "string_ncompare : test1" {
    const str1 = bind.memoryDupz("This is a string", bind.stringLength("This is a string"));
    defer bind.memoryDealloc(str1);

    const str2 = bind.memoryDupz("This is a string", bind.stringLength("This is a string"));
    defer bind.memoryDealloc(str2);

    try expectEqualString(str1, str2);
    try expectTrue(bind.stringNcompare(str1, str2, str1.len) == 0);
}

test "string_ncompare : test2" {
    const str1 = bind.memoryDupz("This is a stringa", bind.stringLength("This is a stringa"));
    defer bind.memoryDealloc(str1);

    const str2 = bind.memoryDupz("This is a stringb", bind.stringLength("This is a stringb"));
    defer bind.memoryDealloc(str2);

    try expectTrue(bind.stringNcompare(str1, str2, str1.len) == -1);
}

test "string_ncompare : test3" {
    const str1 = bind.memoryDupz("This is a stringb", bind.stringLength("This is a stringb"));
    defer bind.memoryDealloc(str1);

    const str2 = bind.memoryDupz("This is a stringa", bind.stringLength("This is a stringa"));
    defer bind.memoryDealloc(str2);

    try expectTrue(bind.stringNcompare(str1, str2, str1.len) == 1);
}

// ***********************************+************************************** //

test "string_nconcat : test1" {
    const source = "This is a string";
    const buffer = bind.memoryAlloc(source.len);
    defer bind.memoryDealloc(buffer);
    _ = bind.stringNconcat(buffer, source, source.len);
    try expectEqualString(buffer, source);
}

test "string_nconcat : test2" {
    const source1 = "Hello, ";
    const source2 = "World!";
    const buffer = bind.memoryAlloc(source1.len + source2.len);
    defer bind.memoryDealloc(buffer);
    _ = bind.stringNconcat(buffer, source1, source1.len);
    _ = bind.stringNconcat(buffer, source2, source2.len);
    try expectEqualString(buffer, source1 ++ source2);
}

test "string_nconcat : test3" {
    const source1 = "";
    const source2 = "World!";
    const buffer = bind.memoryAlloc(source1.len + source2.len);
    defer bind.memoryDealloc(buffer);
    _ = bind.stringNconcat(buffer, source1, source1.len);
    _ = bind.stringNconcat(buffer, source2, source2.len);
    try expectEqualString(buffer, source1 ++ source2);
}

test "string_nconcat : test4" {
    const source1 = "Hello, ";
    const source2 = "";
    const buffer = bind.memoryAlloc(source1.len + source2.len);
    defer bind.memoryDealloc(buffer);
    _ = bind.stringNconcat(buffer, source1, source1.len);
    _ = bind.stringNconcat(buffer, source2, source2.len);
    try expectEqualString(buffer, source1 ++ source2);
}

// ***********************************+************************************** //

test "string_ncopy : test1" {
    const source = "This is a string";
    const buffer = bind.memoryAlloc(source.len);
    defer bind.memoryDealloc(buffer);
    _ = bind.stringNcopy(buffer, source, source.len);
    try expectEqualString(buffer, source);
}

test "string_ncopy: test2" {
    const source1 = "Hello, ";
    const source2 = "World!";
    const buffer = bind.memoryAlloc(source1.len);
    defer bind.memoryDealloc(buffer);
    _ = bind.stringNcopy(buffer, source1, source1.len);
    _ = bind.stringNcopy(buffer, source2, source2.len);
    try expectEqualString(buffer, "World! ");
}

test "string_ncopy: test3" {
    const source1 = "";
    const source2 = "World!";
    const buffer = bind.memoryAlloc(source1.len);
    defer bind.memoryDealloc(buffer);
    _ = bind.stringNcopy(buffer, source1, source1.len);
    _ = bind.stringNcopy(buffer, source2, source2.len);
    try expectEqualString(buffer, "");
}

test "string_ncopy : test4" {
    const source1 = "Hello, ";
    const source2 = "";
    const buffer = bind.memoryAlloc(source1.len + source2.len);
    defer bind.memoryDealloc(buffer);
    _ = bind.stringNcopy(buffer, source1, source1.len);
    _ = bind.stringNcopy(buffer, source2, source2.len);
    try expectEqualString(buffer, source1 ++ source2);
}

// ***********************************+************************************** //

test "string_next_token : test1" {
    const heap = bind.ClibHeapAllocator().init();
    defer heap.deinit();

    const source = bind.memoryDupz("This is a string", 16);
    defer bind.memoryDealloc(source);

    var ptr: []const u8 = source;
    var result1: [*c]u8 = null;
    bind.stringNextToken(heap.allocator, &ptr, &result1, " ");
    try expectEqualString(std.mem.span(result1), "This");
    defer heap.dealloc(std.mem.span(result1));

    var result2: [*c]u8 = null;
    bind.stringNextToken(heap.allocator, &ptr, &result2, " ");
    try expectEqualString(std.mem.span(result2), "is");
    defer heap.dealloc(std.mem.span(result2));

    var result3: [*c]u8 = null;
    bind.stringNextToken(heap.allocator, &ptr, &result3, " ");
    try expectEqualString(std.mem.span(result3), "a");
    defer heap.dealloc(std.mem.span(result3));

    var result4: [*c]u8 = null;
    bind.stringNextToken(heap.allocator, &ptr, &result4, " ");
    try expectEqualString(std.mem.span(result4), "string");
    defer heap.dealloc(std.mem.span(result4));
}

test "string_next_token : test2" {
    const heap = bind.ClibHeapAllocator().init();
    defer heap.deinit();

    const source = bind.memoryDupz("", 1);
    defer bind.memoryDealloc(source);

    var ptr: []const u8 = source;
    var result1: [*c]u8 = null;
    bind.stringNextToken(heap.allocator, &ptr, &result1, " ");
    try expectTrue(result1 == null);
}

test "string_next_token : test3" {
    const heap = bind.ClibHeapAllocator().init();
    defer heap.deinit();

    const source = bind.memoryDupz("T i a s ", 16);
    defer bind.memoryDealloc(source);

    var ptr: []const u8 = source;
    var result1: [*c]u8 = null;
    bind.stringNextToken(heap.allocator, &ptr, &result1, " ");
    try expectEqualString(std.mem.span(result1), "T");
    defer heap.dealloc(std.mem.span(result1));

    var result2: [*c]u8 = null;
    bind.stringNextToken(heap.allocator, &ptr, &result2, " ");
    try expectEqualString(std.mem.span(result2), "i");
    defer heap.dealloc(std.mem.span(result2));

    var result3: [*c]u8 = null;
    bind.stringNextToken(heap.allocator, &ptr, &result3, " ");
    try expectEqualString(std.mem.span(result3), "a");
    defer heap.dealloc(std.mem.span(result3));

    var result4: [*c]u8 = null;
    bind.stringNextToken(heap.allocator, &ptr, &result4, " ");
    try expectEqualString(std.mem.span(result4), "s");
    defer heap.dealloc(std.mem.span(result4));
}

test "string_next_token : test4" {
    const heap = bind.ClibHeapAllocator().init();
    defer heap.deinit();

    const source = bind.memoryDupz("     T i a s      ", 18);
    defer bind.memoryDealloc(source);

    var ptr: []const u8 = source;
    var result1: [*c]u8 = null;
    bind.stringNextToken(heap.allocator, &ptr, &result1, " ");
    try expectEqualString(std.mem.span(result1), "T");
    defer heap.dealloc(std.mem.span(result1));

    var result2: [*c]u8 = null;
    bind.stringNextToken(heap.allocator, &ptr, &result2, " ");
    try expectEqualString(std.mem.span(result2), "i");
    defer heap.dealloc(std.mem.span(result2));

    var result3: [*c]u8 = null;
    bind.stringNextToken(heap.allocator, &ptr, &result3, " ");
    try expectEqualString(std.mem.span(result3), "a");
    defer heap.dealloc(std.mem.span(result3));

    var result4: [*c]u8 = null;
    bind.stringNextToken(heap.allocator, &ptr, &result4, " ");
    try expectEqualString(std.mem.span(result4), "s");
    defer heap.dealloc(std.mem.span(result4));
}

// ***********************************+************************************** //

test "string_rbsearch : test1" {
    const result = try bind.stringRbsearch("This is a string", 'g');
    try expectTrue(result[0] == 'g');
}

test "string_rbsearch : test2" {
    try expectError(Cresult.NotFound, bind.stringRbsearch("This is a test", 'c'));
}

test "string_rbsearch : test3" {
    try expectError(Cresult.NotFound, bind.stringRbsearch("", 'c'));
}

// ***********************************+************************************** //

test "string_reverse : test1" {
    const str = bind.memoryDupz("abcdefhijklmnopqrstuvwxyz", 25);
    defer bind.memoryDealloc(str);

    const result = bind.stringReverse(str);
    try expectEqualString(result, "zyxwvutsrqponmlkjihfedcba");
}

test "string_reverse : test2" {
    const str = bind.memoryDupz("ab", 2);
    defer bind.memoryDealloc(str);

    const result = bind.stringReverse(str);
    try expectEqualString(result, "ba");
}

test "string_reverse : test3" {
    const str = bind.memoryDupz("", 0);
    defer bind.memoryDealloc(str);

    const result = bind.stringReverse(str);
    try expectEqualString(result, "");
}

// ***********************************+************************************** //

test "string_search : test1" {
    const haystack = "This is a very long string with a lot of words";
    var iterator = std.mem.splitAny(u8, haystack, " ");
    while (iterator.next()) |needle| {
        const result = try bind.stringSearch(haystack, needle, haystack.len);
        try expectEqualString(needle, result);
    }
}

test "string_search : test2" {
    const haystack = "This is a very long string with a lot of words";
    const needle = "Zig";
    try expectError(Cresult.NotFound, bind.stringSearch(haystack, needle, haystack.len));
}

test "string_search : test3" {
    const haystack = "This is a very long string with a lot of words";
    const needle = "Zig";
    try expectError(Cresult.NotFound, bind.stringSearch(haystack, needle, 0));
}

test "string_search : test4" {
    const result = bind.clib.string_search(null, @ptrCast("This"), 0);
    try expectTrue(result == null);
}

test "string_search : test5" {
    const result = bind.clib.string_search(@ptrCast("This"), @ptrCast("This"), 0);
    try expectTrue(result == null);
}

test "string_search : test6" {
    const haystack = "This is a very long string with a lot of words";
    const needle = bind.memoryZalloc(0);
    defer bind.memoryDealloc(needle);

    const result = try bind.stringSearch(haystack, needle, haystack.len);
    try expectEqualString(haystack, result);
}

// ***********************************+************************************** //

test "string_span : test1" {
    const result = bind.stringSpan("This is a string", " ");
    try expectTrue(result == 0);
}

test "string_span : test2" {
    const result = bind.stringSpan("This is a string", "z");
    try expectTrue(result == 0);
}

test "string_span : test3" {
    const result = bind.stringSpan("This is a string", "T");
    try expectTrue(result == 1);
}

test "string_span : test4" {
    const result = bind.stringSpan("This is a string", "This");
    try expectTrue(result == 4);
}

// ***********************************+************************************** //

test "string_substring : test1" {
    const heap = bind.ClibHeapAllocator().init();
    defer heap.deinit();

    const str = "This is a very long string";

    const result = bind.stringSubstring(heap.allocator, str, 0, str.len);
    defer heap.dealloc(result);

    try expectEqualString(str, result);
}

test "string_substring : test2" {
    const heap = bind.ClibHeapAllocator().init();
    defer heap.deinit();

    const str = "This is a very long string";

    for (0..@mod(str.len, 2)) |i| {
        const start = i;
        const end = str.len - i;
        const result = bind.stringSubstring(heap.allocator, str, start, end);
        try expectEqualString(str[start..end], result);
        heap.dealloc(result);
    }
}

test "string_substring : test3" {
    const heap = bind.ClibHeapAllocator().init();
    defer heap.deinit();

    const str = "This is a very long string";

    const result = bind.stringSubstring(heap.allocator, str, 0, 4);
    defer heap.dealloc(result);

    try expectEqualString("This", result);
}

// ***********************************+************************************** //

test "string_tokenize : test1" {
    const heap = bind.ClibHeapAllocator().init();
    defer heap.deinit();

    const str = heap.alloc(256);
    _ = bind.stringConcat(str, "This is a very long string to test the tokenizer");
    defer heap.dealloc(str);

    var ptr = str;
    var token = bind.stringTokenize(&ptr, " ");
    try expectEqualString(token, "This");

    token = bind.stringTokenize(&ptr, " ");
    try expectEqualString(token, "is");

    token = bind.stringTokenize(&ptr, " ");
    try expectEqualString(token, "a");

    token = bind.stringTokenize(&ptr, " ");
    try expectEqualString(token, "very");

    token = bind.stringTokenize(&ptr, " ");
    try expectEqualString(token, "long");

    token = bind.stringTokenize(&ptr, " ");
    try expectEqualString(token, "string");

    token = bind.stringTokenize(&ptr, " ");
    try expectEqualString(token, "to");

    token = bind.stringTokenize(&ptr, " ");
    try expectEqualString(token, "test");

    token = bind.stringTokenize(&ptr, " ");
    try expectEqualString(token, "the");

    token = bind.stringTokenize(&ptr, " ");
    try expectEqualString(token, "tokenizer");
}

// test "string_split : test1" {
//     const heap = bind.clib.heap_init();
//     defer _ = bind.clib.heap_deinit(heap);
//     const result = try bind.stringSplit(heap, "This is a test", " ");
//     var itterator = std.mem.splitAny(u8, "This is a test", " ");
//     var i: usize = 0;
//     while (itterator.next()) |split| : (i += 1) {
//         try expectEqualString(split, std.mem.span(result[i]));
//     }
//     defer _ = bind.clib.string_split_destroy(heap, @constCast(@ptrCast(result)));
// }
