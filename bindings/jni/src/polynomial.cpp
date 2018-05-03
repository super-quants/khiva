// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/polynomial.h>
#include <tsa_jni/polynomial.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlongArray JNICALL Java_tsa_Polynomial_polyfit(JNIEnv *env, jobject thisObj, jlong refX, jlong refY,
                                                         jint deg) {
    jint l = 3;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array xx = (af_array)refX;
    af::array x = af::array(xx);
    af_array yy = (af_array)refY;
    af::array y = af::array(yy);
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&xx, x.get());
    af_retain_array(&yy, y.get());

    af_retain_array(&af_p, tsa::polynomial::polyfit(x, y, deg).get());

    tmp[0] = (jlong)xx;
    tmp[1] = (jlong)yy;
    tmp[2] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

JNIEXPORT jlongArray JNICALL Java_tsa_Polynomial_roots(JNIEnv *env, jobject thisObj, jlong ref) {
    jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, tsa::polynomial::roots(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

#ifdef __cplusplus
}
#endif