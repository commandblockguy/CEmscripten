#ifndef H_COMPRESSION
#define H_COMPRESSION

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Decompress a block of zx7 encoded data
 *
 * @param dest Pointer to destination for uncompressed data
 * @param src Pointer to compressed data
*/
void zx7_Decompress(void *dest, const void *src);

#ifdef __cplusplus
}
#endif

#endif