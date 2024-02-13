const std = @import("std");
const mem = std.mem;
const debug = std.debug;
const testing = std.testing;
const process = std.process;
const log = std.log;
const cstd = std.c;
const ascii = std.ascii;

pub const clib = @cImport({
    @cInclude("clib.h");
});

// ***********************************+************************************** //
//                                 helpers                                    //
// ************************************************************************** //

pub const CResult = error{
    NotFound,
    Null,
    OutOfMemory,
};

pub export fn compare(v1: usize, v2: usize) callconv(.C) i64 {
    return (@intCast(v1 - v2));
}

pub const Callocator = clib.struct_s_allocator;

pub const Node = clib.t_list;

pub fn MyList() type {
    return struct {
        const Self = @This();
        list: ?*Node,
        allocator: *Callocator,

        pub fn init(allocator: *Callocator) Self {
            return Self{
                .list = null,
                .allocator = allocator,
            };
        }

        /// t_list *list_create(struct s_allocator *allocator);
        pub fn create(self: Self) ?*Node {
            return (clib.list_create(@ptrCast(self.allocator)));
        }

        /// t_list *list_destroy(struct s_allocator *allocator, t_list *self);
        pub fn destroy(self: Self) void {
            _ = clib.list_destroy(@ptrCast(self.allocator), self.list);
        }

        /// void    list_clear(t_list *list, uint64_t n);
        pub fn clear(self: Self, n: u64) void {
            clib.list_clear(self.list, n);
        }

        /// void *list_remove_at(struct s_allocator *allocator, t_list **self, uint64_t index);
        pub fn removeAt(self: Self, index: usize) usize {
            return (clib.list_remove_at(self.allocator, @constCast(@ptrCast(self.list)), index));
        }

        /// t_list *list_insert_at(struct s_allocator *allocator, t_list **self, void *data, uint64_t index);
        pub fn insertAt(self: Self, uintptr: usize, index: usize) ?*Node {
            return clib.list_insert_at(self.allocator, @constCast(@ptrCast(&self.list)), uintptr, index);
        }

        /// void    *list_peek_at(t_list **self, uint64_t index);
        pub fn peekAt(self: Self, index: usize) usize {
            var list_ptr: [*c]clib.t_list = @constCast(@ptrCast(self.list.?));
            return clib.list_peek_at(&list_ptr, index);
        }

        /// t_list *list_pop_at(t_list **self, uint64_t index);
        pub fn popAt(self: Self, index: usize) ?*Node {
            return clib.list_pop_at(&self.list, index);
        }

        /// t_list *list_push_at(t_list **self, t_list *node, uint64_t index);
        pub fn pushAt(self: Self, node: *Node, index: usize) ?*Node {
            return (clib.list_push_at(&self.list, node, index));
        }

        /// t_list *list_pop_first(struct s_list **head, void *target, t_compare_function compare);
        pub fn popFirst(self: Self, target: usize, cmp: compare) ?*Node {
            return clib.list_pop_first(&self.list, target, cmp);
        }

        /// t_list *list_search(struct s_list *head, void *target, t_compare_function compare);
        pub fn search(self: Self, target: usize, cmp: compare) ?*Node {
            return clib.list_search(self.list, target, cmp);
        }

        /// t_list *list_clone(struct s_allocator *allocator, t_list **self);
        pub fn clone(self: Self) ?*Node {
            return clib.list_clone(self.allocator, &self.list);
        }

        /// uint64_t list_length(t_list *list);
        pub fn len(self: Self) u64 {
            return (clib.list_length(self.list));
        }

        /// t_list *list_concat(t_list **dstl, t_list **srcl);
        pub fn concat(self: Self, srcl: *?*Node) ?*Node {
            return (clib.list_concat(&self.list, srcl));
        }

        /// t_list *list_rotate(t_list **list, int shift);
        pub fn rotate(self: Self, shift: i32) ?*Node {
            return (clib.list_rotate(&self.list, shift));
        }

        /// void    list_sort(t_list **list, int (*f)(void *d1, void *d2));
        pub fn sort(self: Self, cmp: compare) void {
            return (clib.list_sort(&self.list, cmp));
        }
    };
}

pub fn ClibHeapAllocator() type {
    return struct {
        const Self = @This();
        allocator: *Callocator,

        pub fn init() Self {
            return Self{
                .allocator = clib.heap_init(),
            };
        }

        pub fn alloc(self: Self, size: u64) []const u8 {
            return @as([*c]u8, @ptrCast(clib.heap_alloc(self.allocator, size)))[0..size];
        }

        pub fn dealloc(self: Self, ptr: []const u8) void {
            _ = clib.heap_dealloc(self.allocator, @constCast(@ptrCast(ptr.ptr)));
        }

        pub fn deinit(self: Self) void {
            _ = clib.heap_deinit(self.allocator);
        }
    };
}

// ***********************************+************************************** //
//                               Memory                                       //
// ************************************************************************** //

pub fn memoryAlloc(size: u64) []const u8 {
    return (@as([*]u8, @ptrCast(clib.memory_alloc(size).?))[0..size]);
}

pub fn memoryDealloc(ptr: []const u8) void {
    _ = clib.memory_dealloc(@constCast(@ptrCast(ptr.ptr)));
}

pub fn memoryCopy(dest: []const u8, src: []const u8, n: u64) []const u8 {
    const ptr1: ?*anyopaque = @constCast(@ptrCast(dest));
    const ptr2: ?*anyopaque = @constCast(@ptrCast(src));
    return (@as([*c]u8, @ptrCast(clib.memory_copy(ptr1, ptr2, n).?))[0..n]);
}

pub fn memoryCcopy(dest: []const u8, src: []const u8, delim: i32, n: u64) ?[]const u8 {
    const ptr1: ?*anyopaque = @constCast(@ptrCast(dest));
    const ptr2: ?*anyopaque = @constCast(@ptrCast(src));

    if (clib.memory_ccopy(ptr1, ptr2, delim, n)) |some| {
        const len = clib.string_length(@ptrCast(some));
        return (@as([*]u8, @ptrCast(some))[0..len]);
    } else return null;
}

pub fn memoryCompare(dest: []const u8, src: []const u8, n: u64) i32 {
    return (clib.memory_compare(dest.ptr, src.ptr, n));
}

pub fn memoryMove(dest: []const u8, src: []const u8, len: u64) []const u8 {
    const ptr1: ?*anyopaque = @constCast(@ptrCast(dest));
    const ptr2: ?*anyopaque = @constCast(@ptrCast(src));
    return (@as([*c]u8, @ptrCast(clib.memory_move(ptr1, ptr2, len).?))[0..len]);
}

pub fn memorySearch(s: []const u8, c: i32, n: u64) ![]const u8 {
    const ptr1: ?*anyopaque = @constCast(@ptrCast(s));
    const result = clib.memory_search(ptr1, c, n);
    if (result != null) {
        const ret: []const u8 = @as([*]u8, @ptrCast(result))[0..n];
        return (ret);
    } else return CResult.NotFound;
}

pub fn memorySet(dest: []const u8, c: i32, len: u64) []const u8 {
    const ptr1: ?*anyopaque = @constCast(@ptrCast(dest));
    return (@as([*c]u8, @ptrCast(clib.memory_set(ptr1, c, len).?))[0..len]);
}

pub fn memoryZalloc(size: u64) []const u8 {
    return (@as([*c]u8, @ptrCast(clib.memory_zalloc(size).?))[0..size]);
}

pub fn memoryRealloc(ptr: []const u8, osize: u64, nsize: u64) []const u8 {
    const ptr1: ?*anyopaque = @constCast(@ptrCast(ptr));
    return (@as([*c]u8, @ptrCast(clib.memory_realloc(ptr1, osize, nsize).?))[0..nsize]);
}

pub fn memoryDup(m: []const u8, size: u64) []const u8 {
    const ptr: ?*anyopaque = @constCast(@ptrCast(m.ptr));
    const result = clib.memory_dup(ptr, size);
    const slc: []const u8 = @as([*]u8, @ptrCast(result))[0..size];
    return (slc);
}

pub fn memoryDupz(m: []const u8, size: u64) []const u8 {
    const ptr: ?*anyopaque = @constCast(@ptrCast(m.ptr));
    const result = clib.memory_dupz(ptr, size);
    const slc: []const u8 = @as([*]u8, @ptrCast(result))[0..size];
    return (slc);
}

// ***********************************+************************************** //
//                                 Char                                       //
// ************************************************************************** //

pub fn charIsAlnum(ch: i32) bool {
    return (clib.char_is_alnum(ch));
}

pub fn charIsAlpha(ch: i32) bool {
    return (clib.char_is_alpha(ch));
}

pub fn charIsAscii(ch: i32) bool {
    return (clib.char_is_ascii(ch));
}

pub fn charIsBinary(ch: i32) bool {
    return (clib.char_is_binary(ch));
}

pub fn charIsDecimal(ch: i32) bool {
    return (clib.char_is_decimal(ch));
}

pub fn charIsDigit(ch: i32) bool {
    return (clib.char_is_digit(ch));
}

pub fn charIsEven(ch: i32) bool {
    return (clib.char_is_even(ch));
}

pub fn charIsHex(ch: i32) bool {
    return (clib.char_is_hex(ch));
}

pub fn charIsLowercase(ch: i32) bool {
    return (clib.char_is_lowercase(ch));
}

pub fn charIsUppercase(ch: i32) bool {
    return (clib.char_is_uppercase(ch));
}

pub fn charIsNewline(ch: i32) bool {
    return (clib.char_is_newline(ch));
}

pub fn charIsOctal(ch: i32) bool {
    return (clib.char_is_octal(ch));
}

pub fn charIsOdd(ch: i32) bool {
    return (clib.char_is_odd(ch));
}

pub fn charIsPrintable(ch: i32) bool {
    return (clib.char_is_printable(ch));
}
pub fn charIsSpaces(ch: i32) bool {
    return (clib.char_is_spaces(ch));
}

pub fn charIsWhitespace(ch: i32) bool {
    return (clib.char_is_whitespace(ch));
}

pub fn charToLowercase(ch: i32) i32 {
    return (clib.char_to_lowercase(ch));
}

pub fn charToUppercase(ch: i32) i32 {
    return (clib.char_to_uppercase(ch));
}

pub fn charToReversecase(ch: i32) i32 {
    return (clib.char_to_reversecase(ch));
}

// ***********************************+************************************** //
//                                Strings                                     //
// ************************************************************************** //

/// uint8_t *string_bsearch(const uint8_t *s, int32_t c);
pub fn stringBsearch(str: []const u8, c: i32) ![]const u8 {
    const result: ?[*:0]const u8 = clib.string_bsearch(@ptrCast(str[0..]), c);

    if (result != null) {
        return (std.mem.span(result.?));
    } else {
        return (CResult.NotFound);
    }
}

/// int32_t  string_casecompare(const uint8_t *s1, const uint8_t *s2);
pub fn stringCasecompare(str1: []const u8, str2: []const u8) i32 {
    return (clib.string_casecompare(@ptrCast(str1[0..]), @ptrCast(str2[0..])));
}

/// uint8_t *string_clone(struct s_allocator *allocator, const uint8_t *string);
pub fn stringClone(allocator: *Callocator, str: []const u8) []const u8 {
    return (std.mem.span(clib.string_clone(allocator, str.ptr)));
}

/// int32_t  string_compare(const uint8_t *s1, const uint8_t *s2);
pub fn stringCompare(str1: []const u8, str2: []const u8) i32 {
    return (clib.string_compare(str1.ptr, str2.ptr));
}

/// uint8_t *string_concat(uint8_t *s1, const uint8_t *s2);
pub fn stringConcat(str1: []const u8, str2: []const u8) []const u8 {
    const ptr1: [*c]u8 = @constCast(@ptrCast(str1));
    const ptr2: [*c]u8 = @constCast(@ptrCast(str2));
    const result: []const u8 = @as([*c]const u8, @ptrCast(clib.string_concat(ptr1, ptr2)))[0 .. str1.len + str2.len - 1];
    return (result);
}

/// uint8_t *string_copy(uint8_t *dst, const uint8_t *src);
pub fn stringCopy(dst: []const u8, src: []const u8) []const u8 {
    const ptr1: [*c]u8 = @constCast(@ptrCast(dst));
    const ptr2: [*c]u8 = @constCast(@ptrCast(src));
    const result: []const u8 = @as([*c]const u8, @ptrCast(clib.string_copy(ptr1, ptr2)))[0..dst.len];
    return (result);
}

/// uint64_t string_count(const uint8_t *string, int32_t c);
pub fn stringCount(str: []const u8, c: i32) u64 {
    return (clib.string_count(str.ptr, c));
}

/// uint64_t string_cspan(const uint8_t *s, const uint8_t *charset);
pub fn stringCspan(s: []const u8, charset: []const u8) u64 {
    return (clib.string_cspan(s.ptr, charset.ptr));
}

/// uint64_t string_count_leading(const uint8_t *string, int32_t c);
pub fn stringCountLeading(str: []const u8, c: i32) u64 {
    return (clib.string_count_leading(str.ptr, c));
}

/// uint64_t string_count_token(const uint8_t *string, const uint8_t *delim);
pub fn stringCountToken(str: []const u8, delim: []const u8) u64 {
    const ptr1: [*c]const u8 = @ptrCast(str);
    const ptr2: [*c]const u8 = @ptrCast(delim);
    return (clib.string_count_token(ptr1, ptr2));
}

/// uint64_t string_count_trailing(const uint8_t *string, int32_t c);
pub fn stringCountTrailing(str: []const u8, c: i32) u64 {
    return (clib.string_count_trailing(str.ptr, c));
}

// uint64_t string_count_until(const uint8_t *string, int32_t c);
pub fn stringCountUntil(str: []const u8, c: i32) u64 {
    return (clib.string_count_until(str.ptr, c));
}

// uint8_t *string_join(struct s_allocator *allocator, const uint8_t *s1, const uint8_t *s2);
pub fn stringJoin(allocator: *Callocator, s1: []const u8, s2: []const u8) []const u8 {
    const ptr1: [*c]u8 = @constCast(@ptrCast(s1));
    const ptr2: [*c]u8 = @constCast(@ptrCast(s2));
    const len = s1.len + s2.len;
    const result: []const u8 = @as([*c]const u8, @ptrCast(clib.string_join(allocator, ptr1, ptr2)))[0..len];
    return (result);
}

// uint64_t string_lconcat(uint8_t *dst, const uint8_t *src, uint64_t size);
pub fn stringLconcat(s1: []const u8, s2: []const u8, dstsize: u64) u64 {
    const ptr1: [*c]u8 = @constCast(@ptrCast(s1));
    const ptr2: [*c]u8 = @constCast(@ptrCast(s2));
    return (clib.string_lconcat(ptr1, ptr2, dstsize));
}

// uint64_t string_lcopy(uint8_t *dst, const uint8_t *src, uint64_t dsize);
pub fn stringLcopy(s1: []const u8, s2: []const u8, dstsize: u64) u64 {
    const ptr1: [*c]u8 = @constCast(@ptrCast(s1));
    const ptr2: [*c]u8 = @constCast(@ptrCast(s2));
    return (clib.string_lcopy(ptr1, ptr2, dstsize));
}

// uint64_t string_length(const uint8_t *str);
pub fn stringLength(s1: []const u8) u64 {
    return (clib.string_length(s1.ptr));
}

// int32_t  string_ncasecompare(const uint8_t *s1, const uint8_t *s2, uint64_t n);
pub fn stringNcasecompare(str1: []const u8, str2: []const u8, n: u64) i32 {
    const ptr1: [*c]const u8 = @ptrCast(str1);
    const ptr2: [*c]const u8 = @ptrCast(str2);
    return (clib.string_ncasecompare(ptr1, ptr2, n));
}

// uint8_t *string_nclone(struct s_allocator *allocator, const uint8_t *string, uint64_t n);
pub fn stringNclone(allocator: *Callocator, str: []const u8, n: u64) []const u8 {
    const ptr1: [*c]const u8 = @ptrCast(str);
    const result: []const u8 = @as([*c]const u8, @ptrCast(clib.string_nclone(allocator, ptr1, n)))[0..n];
    return (result);
}

// int32_t  string_ncompare(const uint8_t *s1, const uint8_t *s2, uint64_t n);
pub fn stringNcompare(str1: []const u8, str2: []const u8, n: u64) i32 {
    const ptr1: [*c]const u8 = @ptrCast(str1);
    const ptr2: [*c]const u8 = @ptrCast(str2);
    return (clib.string_ncompare(ptr1, ptr2, n));
}

// uint8_t *string_nconcat(uint8_t *s1, const uint8_t *s2, uint64_t n);
pub fn stringNconcat(str1: []const u8, str2: []const u8, n: u64) []const u8 {
    const ptr1: [*c]u8 = @constCast(@ptrCast(str1));
    const ptr2: [*c]const u8 = @ptrCast(str2);
    const result: []const u8 = @as([*c]const u8, @ptrCast(clib.string_nconcat(ptr1, ptr2, n)))[0..n];
    return (result);
}

// uint8_t *string_ncopy(uint8_t *dst, const uint8_t *src, uint64_t n);
pub fn stringNcopy(dst: []const u8, src: []const u8, n: u64) []const u8 {
    const ptr1: [*c]u8 = @constCast(@ptrCast(dst));
    const ptr2: [*c]const u8 = @ptrCast(src);
    const result: []const u8 = @as([*c]const u8, @ptrCast(clib.string_ncopy(ptr1, ptr2, n)))[0..n];
    return (result);
}

// void string_next_token(struct s_allocator *allocator, uint8_t **string, uint8_t **out_token, const uint8_t *delim);
pub fn stringNextToken(allocator: *Callocator, string: []const u8, delim: []const u8, out: [*c][*c]u8) u64 {
    const ptr1: [*c]u8 = @constCast(@ptrCast(string));
    return clib.string_next_token(allocator, ptr1, delim.ptr, out);
}

// uint8_t *string_rbsearch(const uint8_t *s, int32_t c);
pub fn stringRbsearch(str: []const u8, c: i32) ![]const u8 {
    const result: ?[*:0]const u8 = clib.string_rbsearch(@ptrCast(str[0..]), c);

    if (result != null) {
        return (std.mem.span(result.?));
    } else {
        return (CResult.NotFound);
    }
}

// uint8_t *string_reverse(uint8_t *str);
pub fn stringReverse(str: []const u8) []const u8 {
    const ptr1: [*c]u8 = @constCast(@ptrCast(str));
    const result: []const u8 = @as([*c]const u8, @ptrCast(clib.string_reverse(ptr1)))[0..str.len];
    return (result);
}

// uint8_t *string_search(const uint8_t *haystack, const uint8_t *needle, uint64_t len);
pub fn stringSearch(haystack: []const u8, needle: []const u8, len: u64) ![]const u8 {
    const ptr1: [*c]const u8 = @ptrCast(haystack);
    const ptr2: [*c]const u8 = @ptrCast(needle);
    const n = needle.len;
    const result: ?[*:0]const u8 = clib.string_search(ptr1, ptr2, len);
    if (result != null) {
        if (n == 0) {
            const res = std.mem.span(result.?);
            const h = haystack.len;
            return (res[0..h]);
        }
        const res = std.mem.span(result.?);
        return (res[0..n]);
    } else {
        return (CResult.NotFound);
    }
}

// uint64_t string_span(const uint8_t *s, const uint8_t *charset);
pub fn stringSpan(s: []const u8, charset: []const u8) u64 {
    return (clib.string_span(s.ptr, charset.ptr));
}

// uint8_t **string_split(struct s_allocator *allocator, const uint8_t *string, const uint8_t *delim);
pub fn stringSplit(allocator: *Callocator, str: []const u8, delim: []const u8) ![*:null]const [*c]const u8 {
    const result: ?[*:null]const [*c]const u8 = clib.string_split(allocator, str.ptr, delim.ptr);
    if (result) |r| {
        const ret = std.mem.span(r);
        return (ret);
    } else {
        return CResult.Null;
    }
}

// void **string_split_destroy(struct s_allocator *allocator, uint8_t **split);
pub fn stringSplitDestoy(allocator: *Callocator, str: []const u8) [][]const u8 {
    return (clib.string_split_destroy(allocator, str.ptr));
}

// uint8_t *string_substring(struct s_allocator *allocator, uint8_t const *s, uint64_t start, uint64_t len);
pub fn stringSubstring(allocator: *Callocator, string: []const u8, start: u64, len: u64) []const u8 {
    const ptr1: [*c]const u8 = @ptrCast(string);
    const result: []const u8 = @as([*]u8, @ptrCast(clib.string_substring(allocator, ptr1, start, len)))[0..len];
    return (result);
}

// uint8_t *string_tokenize(const uint8_t **string, const uint8_t *delim);
pub fn stringTokenize(string: *[]const u8, delim: []const u8) []const u8 {
    const ptr1: [*c][*c]u8 = @constCast(@ptrCast(string));
    const len = stringCspan(string.*, delim);
    const result: []const u8 = @as([*]u8, @ptrCast(clib.string_tokenize(ptr1, delim.ptr)))[0..len];
    return (result);
}

// uint8_t *string_tolower(uint8_t *string);
pub fn stringToLower(string: []const u8) []const u8 {
    const ptr1: [*c]u8 = @constCast(@ptrCast(string));
    const result: []const u8 = @as([*]u8, @ptrCast(clib.string_tolower(ptr1)))[0..string.len];
    return (result);
}

// uint8_t *string_toupper(uint8_t *string);
pub fn stringToUpper(string: []const u8) []const u8 {
    const ptr1: [*c]u8 = @constCast(@ptrCast(string));
    const result: []const u8 = @as([*]u8, @ptrCast(clib.string_toupper(ptr1)))[0..string.len];
    return (result);
}
