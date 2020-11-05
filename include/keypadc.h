#include <stdint.h>

typedef uint8_t kb_key_t;   /**< Normal key type */
typedef uint16_t kb_lkey_t; /**< Long key type   */

#define kb_ScanGroup(row) kb_Data[row]
uint8_t kb_AnyKey(void);

#define kb_Scan()

#define kb_IsDown(lkey) \
(kb_Data[(lkey) >> 8] & (lkey))

extern uint8_t kb_Data[8];

/* Keyboard group 1 */
#define kb_Graph    (1<<0)
#define kb_Trace    (1<<1)
#define kb_Zoom     (1<<2)
#define kb_Window   (1<<3)
#define kb_Yequ     (1<<4)
#define kb_2nd      (1<<5)
#define kb_Mode     (1<<6)
#define kb_Del      (1<<7)

/* Keyboard group 2 */
#define kb_Sto      (1<<1)
#define kb_Ln       (1<<2)
#define kb_Log      (1<<3)
#define kb_Square   (1<<4)
#define kb_Recip    (1<<5)
#define kb_Math     (1<<6)
#define kb_Alpha    (1<<7)

/* Keyboard group 3 */
#define kb_0        (1<<0)
#define kb_1        (1<<1)
#define kb_4        (1<<2)
#define kb_7        (1<<3)
#define kb_Comma    (1<<4)
#define kb_Sin      (1<<5)
#define kb_Apps     (1<<6)
#define kb_GraphVar (1<<7)

/* Keyboard group 4 */
#define kb_DecPnt   (1<<0)
#define kb_2        (1<<1)
#define kb_5        (1<<2)
#define kb_8        (1<<3)
#define kb_LParen   (1<<4)
#define kb_Cos      (1<<5)
#define kb_Prgm     (1<<6)
#define kb_Stat     (1<<7)

/* Keyboard group 5 */
#define kb_Chs      (1<<0)
#define kb_3        (1<<1)
#define kb_6        (1<<2)
#define kb_9        (1<<3)
#define kb_RParen   (1<<4)
#define kb_Tan      (1<<5)
#define kb_Vars     (1<<6)

/* Keyboard group 6 */
#define kb_Enter    (1<<0)
#define kb_Add      (1<<1)
#define kb_Sub      (1<<2)
#define kb_Mul      (1<<3)
#define kb_Div      (1<<4)
#define kb_Power    (1<<5)
#define kb_Clear    (1<<6)

/* Keyboard group 7 */
#define kb_Down     (1<<0)
#define kb_Left     (1<<1)
#define kb_Right    (1<<2)
#define kb_Up       (1<<3)

/* Keyboard group 1 */
#define kb_KeyGraph     ((kb_lkey_t)(1 << 8 | 1<<0))
#define kb_KeyTrace     ((kb_lkey_t)(1 << 8 | 1<<1))
#define kb_KeyZoom      ((kb_lkey_t)(1 << 8 | 1<<2))
#define kb_KeyWindow    ((kb_lkey_t)(1 << 8 | 1<<3))
#define kb_KeyYequ      ((kb_lkey_t)(1 << 8 | 1<<4))
#define kb_Key2nd       ((kb_lkey_t)(1 << 8 | 1<<5))
#define kb_KeyMode      ((kb_lkey_t)(1 << 8 | 1<<6))
#define kb_KeyDel       ((kb_lkey_t)(1 << 8 | 1<<7))

/* Keyboard group 2 */
#define kb_KeyStore     ((kb_lkey_t)(2 << 8 | 1<<1))
#define kb_KeyLn        ((kb_lkey_t)(2 << 8 | 1<<2))
#define kb_KeyLog       ((kb_lkey_t)(2 << 8 | 1<<3))
#define kb_KeySquare    ((kb_lkey_t)(2 << 8 | 1<<4))
#define kb_KeyRecip     ((kb_lkey_t)(2 << 8 | 1<<5))
#define kb_KeyMath      ((kb_lkey_t)(2 << 8 | 1<<6))
#define kb_KeyAlpha     ((kb_lkey_t)(2 << 8 | 1<<7))

/* Keyboard group 3 */
#define kb_Key0         ((kb_lkey_t)(3 << 8 | 1<<0))
#define kb_Key1         ((kb_lkey_t)(3 << 8 | 1<<1))
#define kb_Key4         ((kb_lkey_t)(3 << 8 | 1<<2))
#define kb_Key7         ((kb_lkey_t)(3 << 8 | 1<<3))
#define kb_KeyComma     ((kb_lkey_t)(3 << 8 | 1<<4))
#define kb_KeySin       ((kb_lkey_t)(3 << 8 | 1<<5))
#define kb_KeyApps      ((kb_lkey_t)(3 << 8 | 1<<6))
#define kb_KeyGraphVar  ((kb_lkey_t)(3 << 8 | 1<<7))

/* Keyboard group 4 */
#define kb_KeyDecPnt    ((kb_lkey_t)(4 << 8 | 1<<0))
#define kb_Key2         ((kb_lkey_t)(4 << 8 | 1<<1))
#define kb_Key5         ((kb_lkey_t)(4 << 8 | 1<<2))
#define kb_Key8         ((kb_lkey_t)(4 << 8 | 1<<3))
#define kb_KeyLParen    ((kb_lkey_t)(4 << 8 | 1<<4))
#define kb_KeyCos       ((kb_lkey_t)(4 << 8 | 1<<5))
#define kb_KeyPrgm      ((kb_lkey_t)(4 << 8 | 1<<6))
#define kb_KeyStat      ((kb_lkey_t)(4 << 8 | 1<<7))

/* Keyboard group 5 */
#define kb_KeyChs      ((kb_lkey_t)(5 << 8 | 1<<0))
#define kb_Key3        ((kb_lkey_t)(5 << 8 | 1<<1))
#define kb_Key6        ((kb_lkey_t)(5 << 8 | 1<<2))
#define kb_Key9        ((kb_lkey_t)(5 << 8 | 1<<3))
#define kb_KeyRParen   ((kb_lkey_t)(5 << 8 | 1<<4))
#define kb_KeyTan      ((kb_lkey_t)(5 << 8 | 1<<5))
#define kb_KeyVars     ((kb_lkey_t)(5 << 8 | 1<<6))

/* Keyboard group 6 */
#define kb_KeyEnter    ((kb_lkey_t)(6 << 8 | 1<<0))
#define kb_KeyAdd      ((kb_lkey_t)(6 << 8 | 1<<1))
#define kb_KeySub      ((kb_lkey_t)(6 << 8 | 1<<2))
#define kb_KeyMul      ((kb_lkey_t)(6 << 8 | 1<<3))
#define kb_KeyDiv      ((kb_lkey_t)(6 << 8 | 1<<4))
#define kb_KeyPower    ((kb_lkey_t)(6 << 8 | 1<<5))
#define kb_KeyClear    ((kb_lkey_t)(6 << 8 | 1<<6))

/* Keyboard group 7 */
#define kb_KeyDown     ((kb_lkey_t)(7 << 8 | 1<<0))
#define kb_KeyLeft     ((kb_lkey_t)(7 << 8 | 1<<1))
#define kb_KeyRight    ((kb_lkey_t)(7 << 8 | 1<<2))
#define kb_KeyUp       ((kb_lkey_t)(7 << 8 | 1<<3))

#define kb_Store        kb_Sto
#define kb_KeyPgrm      kb_KeyPrgm
#define kb_group_0      0
#define kb_group_1      1
#define kb_group_2      2
#define kb_group_3      3
#define kb_group_4      4
#define kb_group_5      5
#define kb_group_6      6
#define kb_group_7      7

