#ifndef H_FLATCC_DEFS
#define H_FLATCC_DEFS

/**
 * \file rpmio/rpmdefs.h
 * Compiler attributes for __GNUC__.
 */

/*
 * Miscellaneous utility macros:
 * - portability wrappers for various gcc extensions like __attribute__()
 * - ...
 *
 * Copied from glib, names replaced to avoid clashing with glib.
 *
 */

/* Here we provide FLATCC_GNUC_EXTENSION as an alias for __extension__,
 * where this is valid. This allows for warningless compilation of
 * "long long" types even in the presence of '-ansi -pedantic'. 
 */
#if     __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 8)
#  define FLATCC_GNUC_EXTENSION __extension__
#else
#  define FLATCC_GNUC_EXTENSION
#endif

/* Provide macros to feature the GCC function attribute.
 */
#if    __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 96)
#define FLATCC_GNUC_PURE				\
  __attribute__((__pure__))
#define FLATCC_GNUC_MALLOC				\
  __attribute__((__malloc__))
#else
#define FLATCC_GNUC_PURE
#define FLATCC_GNUC_MALLOC
#endif

#if     (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
#define FLATCC_GNUC_ALLOC_SIZE(x) __attribute__((__alloc_size__(x)))
#define FLATCC_GNUC_ALLOC_SIZE2(x,y) __attribute__((__alloc_size__(x,y)))
#else
#define FLATCC_GNUC_ALLOC_SIZE(x)
#define FLATCC_GNUC_ALLOC_SIZE2(x,y)
#endif

#if     __GNUC__ >= 4
#define FLATCC_GNUC_NULL_TERMINATED __attribute__((__sentinel__))
#else
#define FLATCC_GNUC_NULL_TERMINATED
#endif

#if     __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 4)
#define FLATCC_GNUC_PRINTF( format_idx, arg_idx )	\
  __attribute__((__format__ (__printf__, format_idx, arg_idx)))
#define FLATCC_GNUC_SCANF( format_idx, arg_idx )	\
  __attribute__((__format__ (__scanf__, format_idx, arg_idx)))
#define FLATCC_GNUC_FORMAT( arg_idx )		\
  __attribute__((__format_arg__ (arg_idx)))
#define FLATCC_GNUC_NORETURN			\
  __attribute__((__noreturn__))
#define FLATCC_GNUC_CONST				\
  __attribute__((__const__))
#define FLATCC_GNUC_UNUSED				\
  __attribute__((__unused__))
#define FLATCC_GNUC_USED				\
  __attribute__((__used__))
#define FLATCC_GNUC_NO_INSTRUMENT			\
  __attribute__((__no_instrument_function__))
#else   /* !__GNUC__ */
#define FLATCC_GNUC_PRINTF( format_idx, arg_idx )
#define FLATCC_GNUC_SCANF( format_idx, arg_idx )
#define FLATCC_GNUC_FORMAT( arg_idx )
#define FLATCC_GNUC_NORETURN
#define FLATCC_GNUC_CONST
#define FLATCC_GNUC_UNUSED
#define FLATCC_GNUC_NO_INSTRUMENT
#endif  /* !__GNUC__ */

#if    __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1)
#define FLATCC_GNUC_DEPRECATED			\
  __attribute__((__deprecated__))
#define FLATCC_GNUC_DEPRECATED_MSG(msg)		\
  __attribute__((__deprecated__(msg)))
#else
#define FLATCC_GNUC_DEPRECATED
#define FLATCC_GNUC_DEPRECATED_MSG(msg)
#endif /* __GNUC__ */

#if     __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3)
#define FLATCC_GNUC_MAY_ALIAS __attribute__((may_alias))
#define FLATCC_GNUC_NONNULL( ... )	\
  __attribute__((__nonnull__ (__VA_ARGS__)))
#else
#define FLATCC_GNUC_MAY_ALIAS
#define FLATCC_GNUC_NONNULL( ... )
#endif

#if    __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#define FLATCC_GNUC_WARN_UNUSED_RESULT 		\
  __attribute__((warn_unused_result))
#else
#define FLATCC_GNUC_WARN_UNUSED_RESULT
#endif /* __GNUC__ */

#if    __GNUC__ >= 4 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3)
#  define FLATCC_GNUC_INTERNAL __attribute__((visibility("hidden")))
#else
#  define FLATCC_GNUC_INTERNAL
#endif

/* if !__clang__ &&  __GNUC__ == 4 && __GNUC_MINOR__ >= 7 */
#if defined(HAVE_GNUC_TM_ATOMIC) && !defined(__SANITIZE_ADDRESS__)
#  define FLATCC_GNUC_TM_SAFE	__attribute__((transaction_safe))
#  define FLATCC_GNUC_TM_PURE	__attribute__((transaction_pure))
#  define FLATCC_GNUC_TM_CALLABLE	__attribute__((transaction_callable))
#  define FLATCC_GNUC_TM_UNSAFE	__attribute__((transaction_unsafe))
#  define FLATCC_GNUC_TM_MAYCANCEL __attribute__((transaction_may_cancel_outer))
#  define FLATCC_GNUC_TM_WRAP(func) __attribute__((transaction_wrap(func)))
#  define FLATCC_GNUC_TM_ATOMIC	__transaction_atomic	/* XXX [[outer]] */
#  define FLATCC_GNUC_TM_RELAXED	__transaction_relaxed
#  define FLATCC_GNUC_TM_CANCEL	__transaction_cancel	/* XXX [[outer]] */
#else
#  define FLATCC_GNUC_TM_SAFE
#  define FLATCC_GNUC_TM_PURE
#  define FLATCC_GNUC_TM_CALLABLE
#  define FLATCC_GNUC_TM_UNSAFE
#  define FLATCC_GNUC_TM_MAYCANCEL
#  define FLATCC_GNUC_TM_WRAP(func)
#  define FLATCC_GNUC_TM_ATOMIC
#  define FLATCC_GNUC_TM_RELAXED
#  define FLATCC_GNUC_TM_CANCEL
#endif

#if defined(__has_feature)
# if __has_feature(address_sanitizer)
#   define  FLATCC_GNUC_NOASAN		__attribute__((no_sanitize("address")))
#   define  FLATCC_GNUC_NOBOUNDS		__attribute__((no_sanitize("bounds")))
#   define  FLATCC_GNUC_NOUNDEFINED	__attribute__((no_sanitize("undefined")))
# else
#   define  FLATCC_GNUC_NOASAN
#   define  FLATCC_GNUC_NOBOUNDS
#   define  FLATCC_GNUC_NOUNDEFINED
# endif
#else
#   define  FLATCC_GNUC_NOASAN
#   define  FLATCC_GNUC_NOBOUNDS
#   define  FLATCC_GNUC_NOUNDEFINED
#endif

/* Guard C code in headers, while including them from C++ */
#ifdef  __cplusplus
# define FLATCC_BEGIN_DECLS  extern "C" {
# define FLATCC_END_DECLS    }
#else
# define FLATCC_BEGIN_DECLS
# define FLATCC_END_DECLS
#endif

#endif /* H_FLATCC_DEFS */
