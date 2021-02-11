/*
 * Copyright (c) 2021 Guilherme Janczak
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


#include <limits.h>

/* COMPLEMENT: holds the machine's signed encoding.
 *
 * 1 on one's complement.
 * 2 on two's complement.
 * 3 on sign and magnitude.
 */
#define COMPLEMENT (~1 == -1 ? 1 : (~1 + 1) == -1 ? 2 : 3)

/* isaddundef: does _a+_b overflow? */
int
isaddundef(int _a, int _b)
{
	unsigned int a = _a;
	unsigned int b = _b;
	unsigned int sum;
	/*
	 * deadtest == 0 on 2's complement, otherwise only the sign bit is set.
	 */
	const unsigned int deadtest = ~(~0U >> (COMPLEMENT != 2));
	const unsigned int shift = sizeof(shift) * CHAR_BIT - 1;

	sum = a + b;
	/*
	 * Dead code on 2's complement.
	 * On other signed encodings, if the sum results in just the sign bit
	 * being set, there's overflow into negative zero.
	 */
	if (sum != 0 && (sum ^ deadtest) == 0)
		return (1);
	return ((~(a ^ b) & (sum ^ a)) >> shift);
}
