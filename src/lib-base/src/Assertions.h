#ifndef ASSERTIONS_H_INCLUDED
#define ASSERTIONS_H_INCLUDED

#define ASSERT_POSITIVE_OR_RET_FALSE(integer) if (integer<0) return false;
#define ASSERT_POSITIVE_OR_RET_ZERO(integer) if (integer<0) return 0;
#define ASSERT_POSITIVE_OR_RET_OBJ(integer, obj) if (integer<0) return obj;
#define ASSERT_TRUE_OR_RET_NEGATIVE(condition) if (!(condition)) return -1;
#define ASSERT_TRUE_OR_RET_FALSE(condition) if (!(condition)) return false;

#endif // ASSERTIONS_H_INCLUDED
