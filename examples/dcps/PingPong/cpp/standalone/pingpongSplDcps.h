#ifndef PINGPONGSPLTYPES_H
#define PINGPONGSPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "ccpp_pingpong.h"


extern c_metaObject __pingpong_pingpong__load (c_base base);

extern const char *pingpong_PP_min_msg_metaDescriptor[];
extern const int pingpong_PP_min_msg_metaDescriptorArrLength;
extern const int pingpong_PP_min_msg_metaDescriptorLength;
extern c_metaObject __pingpong_PP_min_msg__load (c_base base);
struct _pingpong_PP_min_msg ;
extern  v_copyin_result __pingpong_PP_min_msg__copyIn(c_base base, const struct pingpong::PP_min_msg *from, struct _pingpong_PP_min_msg *to);
extern  void __pingpong_PP_min_msg__copyOut(const void *_from, void *_to);
struct _pingpong_PP_min_msg {
    c_ulong block;
    c_ulong count;
};

extern c_metaObject __pingpong_seq_char__load (c_base base);
typedef c_sequence _pingpong_seq_char;

extern const char *pingpong_PP_seq_msg_metaDescriptor[];
extern const int pingpong_PP_seq_msg_metaDescriptorArrLength;
extern const int pingpong_PP_seq_msg_metaDescriptorLength;
extern c_metaObject __pingpong_PP_seq_msg__load (c_base base);
struct _pingpong_PP_seq_msg ;
extern  v_copyin_result __pingpong_PP_seq_msg__copyIn(c_base base, const struct pingpong::PP_seq_msg *from, struct _pingpong_PP_seq_msg *to);
extern  void __pingpong_PP_seq_msg__copyOut(const void *_from, void *_to);
struct _pingpong_PP_seq_msg {
    c_ulong block;
    c_ulong count;
    _pingpong_seq_char payload;
};

extern const char *pingpong_PP_string_msg_metaDescriptor[];
extern const int pingpong_PP_string_msg_metaDescriptorArrLength;
extern const int pingpong_PP_string_msg_metaDescriptorLength;
extern c_metaObject __pingpong_PP_string_msg__load (c_base base);
struct _pingpong_PP_string_msg ;
extern  v_copyin_result __pingpong_PP_string_msg__copyIn(c_base base, const struct pingpong::PP_string_msg *from, struct _pingpong_PP_string_msg *to);
extern  void __pingpong_PP_string_msg__copyOut(const void *_from, void *_to);
struct _pingpong_PP_string_msg {
    c_ulong block;
    c_ulong count;
    c_string a_string;
};

extern c_metaObject __pingpong_string_40__load (c_base base);
typedef c_string _pingpong_string_40;

extern const char *pingpong_PP_fixed_msg_metaDescriptor[];
extern const int pingpong_PP_fixed_msg_metaDescriptorArrLength;
extern const int pingpong_PP_fixed_msg_metaDescriptorLength;
extern c_metaObject __pingpong_PP_fixed_msg__load (c_base base);
struct _pingpong_PP_fixed_msg ;
extern  v_copyin_result __pingpong_PP_fixed_msg__copyIn(c_base base, const struct pingpong::PP_fixed_msg *from, struct _pingpong_PP_fixed_msg *to);
extern  void __pingpong_PP_fixed_msg__copyOut(const void *_from, void *_to);
struct _pingpong_PP_fixed_msg {
    c_ulong block;
    c_ulong count;
    c_char a_char;
    c_octet a_octet;
    c_short a_short;
    c_ushort a_ushort;
    c_long a_long;
    c_ulong a_ulong;
    c_longlong a_longlong;
    c_ulonglong a_ulonglong;
    c_float a_float;
    c_double a_double;
    c_bool a_boolean;
    _pingpong_string_40 a_bstring;
};

extern const char *pingpong_PP_array_msg_metaDescriptor[];
extern const int pingpong_PP_array_msg_metaDescriptorArrLength;
extern const int pingpong_PP_array_msg_metaDescriptorLength;
extern c_metaObject __pingpong_PP_array_msg__load (c_base base);
struct _pingpong_PP_array_msg ;
extern  v_copyin_result __pingpong_PP_array_msg__copyIn(c_base base, const struct pingpong::PP_array_msg *from, struct _pingpong_PP_array_msg *to);
extern  void __pingpong_PP_array_msg__copyOut(const void *_from, void *_to);
struct _pingpong_PP_array_msg {
    c_ulong block;
    c_ulong count;
    c_char str_arr_char[10];
    c_octet str_arr_octet[10];
    c_short str_arr_short[10];
    c_ushort str_arr_ushort[10];
    c_long str_arr_long[10];
    c_ulong str_arr_ulong[10];
    c_longlong str_arr_longlong[10];
    c_ulonglong str_arr_ulonglong[10];
    c_float str_arr_float[10];
    c_double str_arr_double[10];
    c_bool str_arr_boolean[11];
};

extern const char *pingpong_PP_bseq_msg_metaDescriptor[];
extern const int pingpong_PP_bseq_msg_metaDescriptorArrLength;
extern const int pingpong_PP_bseq_msg_metaDescriptorLength;
extern c_metaObject __pingpong_PP_bseq_msg__load (c_base base);
struct _pingpong_PP_bseq_msg ;
extern  v_copyin_result __pingpong_PP_bseq_msg__copyIn(c_base base, const struct pingpong::PP_bseq_msg *from, struct _pingpong_PP_bseq_msg *to);
extern  void __pingpong_PP_bseq_msg__copyOut(const void *_from, void *_to);
struct _pingpong_PP_bseq_msg {
    c_ulong block;
    c_ulong count;
    c_sequence seq_char;
    c_sequence seq_octets;
    c_sequence seq_short;
    c_sequence seq_ushort;
    c_sequence seq_long;
    c_sequence seq_ulong;
    c_sequence seq_longlong;
    c_sequence seq_ulonglong;
    c_sequence seq_float;
    c_sequence seq_double;
    c_sequence seq_boolean;
};

extern const char *pingpong_PP_quit_msg_metaDescriptor[];
extern const int pingpong_PP_quit_msg_metaDescriptorArrLength;
extern const int pingpong_PP_quit_msg_metaDescriptorLength;
extern c_metaObject __pingpong_PP_quit_msg__load (c_base base);
struct _pingpong_PP_quit_msg ;
extern  v_copyin_result __pingpong_PP_quit_msg__copyIn(c_base base, const struct pingpong::PP_quit_msg *from, struct _pingpong_PP_quit_msg *to);
extern  void __pingpong_PP_quit_msg__copyOut(const void *_from, void *_to);
struct _pingpong_PP_quit_msg {
    c_bool quit;
};

#undef OS_API
#endif
