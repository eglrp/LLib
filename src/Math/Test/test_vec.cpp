#include <iostream>
#include "../Vec/vec_header.h"
#include "../../Utility/test.h"

using namespace LLib;
using namespace LLib::Math;

int test_id = 0;

int main(int argc, char **argv)
{

// **************************************************************************
// ******************************   Vec2   **********************************
// **************************************************************************

  // LOG("Start Testing vec2!");
  // SEP();

  // LOG("Static function Testing!");
  // TEST("(0,0)", vec2i::zeros());
  // TEST("(1,1)", vec2i::ones());
  // LOG("Constructor Testing!");
  // vec2<int> vi00;
  // TEST("(0,0)", vi00);                    // 1
  // vec2<int> vi11(1);
  // TEST("(1,1)", vi11);                    // 2
  // vec2<float> vf23(2, 3);
  // TEST("(2,3)", vf23);                    // 3
  // vec2<double> vd11(vi11.toType<double>().getData());
  // TEST("(1,1)", vd11);                    // 4
  // vec2<float> vf23_(vf23);
  // TEST("(2,3)", vf23_);                   // 5

  // LOG("Operator Testing!");
  // TEST(2, vf23[0]);                       // 6
  // TEST(3, vf23[1]);                       // 7
  // // TEST("wrong!", vf23[3]);
  // vf23[0] = 4;
  // TEST("(4,3)", vf23);                    // 8
  // vec2<float> vf11 = vd11.toType<float>();
  // TEST("(1,1)", vf11);                    // 9
  // vec2<float> vf33 = 3;
  // TEST("(3,3)", vf33);                    // 10
  // vf11 += 1;
  // TEST("(2,2)", vf11);                    // 11
  // vf11 += vf11;
  // TEST("(4,4)", vf11);                    // 12
  // vf11 -= 2;
  // TEST("(2,2)", vf11);                    // 13
  // vf11 -= vec2<float>(1);
  // TEST("(1,1)", vf11);                    // 14
  // vf11 *= 2;
  // TEST("(2,2)", vf11);                    // 15
  // vf11 *= vec2<float>(2);
  // TEST("(4,4)", vf11);                    // 16
  // vf11 /= 2;
  // TEST("(2,2)", vf11);                    // 17
  // vf11 /= vec2<float>(2);
  // TEST("(1,1)", vf11);                    // 18
  // vec2<int> r1 = vi11 + vi11;
  // TEST("(2,2)", r1);                      // 19
  // vec2<int> r2 = vi11 + 2;
  // TEST("(3,3)", r2);                      // 20
  // vec2<int> r3 = 2 + vi11;
  // TEST("(3,3)", r3);                      // 21
  // vec2<int> r4 = vi11 - vi11;
  // TEST("(0,0)", r4);                      // 22
  // vec2<int> r5 = vi11 - 2;
  // TEST("(-1,-1)", r5);                    // 23
  // vec2<int> r6 = 2 -vi11;
  // TEST("(1,1)", r6);                      // 24
  // vec2<float> vf11_ = vi11.toType<float>();
  // vec2<float> r7 = vf11_ * 2;
  // TEST("(2,2)", r7);                      // 25
  // vec2<float> r8 = 2 * vf11_;
  // TEST("(2,2)", r8);                      // 26
  // vec2<float> r9 = vec2<float>(3) * vf11_;
  // TEST("(3,3)", r9);                      // 27
  // vec2<float> r10 = vf11_ / 2;
  // TEST("(0.5,0.5)", r10);                 // 28
  // vec2<float> r11 = 2 / vf11_;
  // TEST("(2,2)", r11);                     // 29
  // vec2<float> r12 = vf11_ / vec2<float>(0.5);
  // TEST("(2,2)", r12);                     // 30
  // // vec2<float> r13 = vf11_ / 0.0;
  // bool equal1 = vec2<float>(1,2) == vec2<float>(1,2);
  // bool nequal1 = vec2<float>(1,2) != vec2<float>(1,2);
  // bool equal2 = vec2<float>(1,2) == vec2<float>(0,2);
  // bool nequal2 = vec2<float>(1,2) != vec2<float>(0,2);
  // TEST("1", equal1);                      // 31
  // TEST("0", nequal1);                     // 32
  // TEST("0", equal2);                      // 33
  // TEST("1", nequal2);                     // 34
  // float r14 = dot(vec2<float>(2,3), vec2<float>(2,3));
  // float r15 = vec2<float>(2,3).dot(vec2<float>(2,3));
  // TEST("13", r14);                        // 35
  // TEST("13", r15);                        // 36

  // LOG("Length Testing!");
  // double l2 = vec2<float>(3,4).lengthSq();
  // double l = vec2<float>(3,4).length();
  // TEST("25", l2);                         // 37
  // TEST("5", l);                           // 38

  // LOG("Distance Testing!");
  // double d2 = distSq(vec2<float>(2,3), vec2<float>(1,2));
  // double d = dist(vec2<float>(2,3), vec2<float>(1,2));
  // TEST("2", d2);                          // 39
  // TEST("1.414", d);                       // 40

  // LOG("Normalize Testing!");
  // vec2<float> n(3,4);
  // n.normalize();
  // vec2<float> gn = vec2<float>(3,4).getNormalize();
  // TEST("(0.6,0.8)", n);                   // 41
  // TEST("(0.6,0.8)", gn);                  // 42

  // LOG("<< / >> Testing!");
  // vec2<float> r;
  // // std::cin >> r;                       // TODO
  // std::cout << r << std::endl;

  // LOG("Math TEsting!");
  // vec2<float> r16 = min(vec2<float>(1,4), vec2<float>(2,3));
  // vec2<float> r17 = min(vec2<float>(1,3), 2);
  // TEST("(1,3)", r16);                     // 43
  // TEST("(1,2)", r17);                     // 44
  // vec2<float> r18 = max(vec2<float>(1,4), vec2<float>(2,3));
  // vec2<float> r19 = max(2, vec2<float>(1,4));
  // TEST("(2,4)", r18);                     // 45
  // TEST("(2,4)", r19);                     // 46
  // vec2<float> abs_ = abs(vec2<float>(-2, 1));
  // TEST("(2,1)", abs_);                    // 47
  // vec2<int> floor_ = floor(vec2<float>(2.6, 3.1));
  // vec2<int> ceil_ = ceil(vec2<float>(2.6, 3.1));
  // vec2<int> round_ = round(vec2<float>(2.6, 3.1));
  // TEST("(2,3)", floor_);                  // 48
  // TEST("(3,4)", ceil_);                   // 49
  // TEST("(3,3)", round_);                  // 50
  // vec2<float> frac_ = frac(vec2<float>(2.6, 3.1));
  // TEST("(0.6,0.1)", frac_);               // 51
  // vec2<float> v1;
  // vec2<float> v2 = v1 + 0.00001;
  // vec2<float> v3 = v1 + 0.0000001;
  // TEST("0", floatEqual(v1, v2));          // 52
  // TEST("1", floatEqual(v1, v3));          // 53

  // SEP();
  // SEP();

// **************************************************************************
// ******************************   Vec3   **********************************
// **************************************************************************


  // LOG("Start Testing vec3!");
  // SEP();

  // LOG("Static function Testing!");
  // TEST("(0,0,0)", vec3i::zeros());         // 0
  // TEST("(1,1,1)", vec3i::ones());          // 1

  // LOG("Constructor Testing!");
  // vec3<int> vi1;
  // TEST("(0,0,0)", vi1);                    // 2
  // vec3<int> vi2(1);
  // TEST("(1,1,1)", vi2);                    // 3
  // vec3<float> vf3(1, 2, 3);
  // TEST("(1,2,3)", vf3);                    // 4
  // vec3<double> vd4(vi1.toType<double>().getData());
  // TEST("(1,1,1)", vd4);                    // 5
  // vec3<float> vf3_(vf3);
  // TEST("(1,2,3)", vf3_);                   // 6
  // vec3<float> vf5(vec2<float>(1,1),2);
  // TEST("(1,1,2)", vf5);                    // 7

  // LOG("Operator Testing!");
  // TEST(1, vf3[0]);                         // 8
  // TEST(2, vf3[1]);                         // 9
  // // TEST("wrong!", vf3[4]);
  // vf3[0] = 4;
  // TEST("(4,2,3)", vf3);                    // 10
  // vec3<float> vf6 = vi1.toType<float>();
  // TEST("(0,0,0)", vf6);                    // 11
  // vec3<float> vf7 = 3;
  // TEST("(3,3,3)", vf7);                    // 12
  // TEST("(-3,-3,-3)", -vf7);                // 13
  // vec3<float> vf8(1,2,3);
  // vf8 += 1;
  // TEST("(2,3,4)", vf8);                    // 14
  // vf8 += vf8;
  // TEST("(4,6,8)", vf8);                    // 15
  // vf8 -= 2;
  // TEST("(2,4,6)", vf8);                    // 16
  // vf8 -= vec3<float>(1);
  // TEST("(1,3,5)", vf8);                    // 17
  // vf8 *= 2;
  // TEST("(2,6,10)", vf8);                   // 18
  // vf8 *= vec3<float>(2);
  // TEST("(4,12,20)", vf8);                  // 19
  // vf8 /= 2;
  // TEST("(2,6,10)", vf8);                   // 20
  // vf8 /= vec3<float>(2);
  // TEST("(1,3,5)", vf8);                    // 21
  // vec3<float> r1 = vf8 + vf8;
  // TEST("(2,6,10)", r1);                    // 22
  // vec3<float> r2 = vf8 + 2;
  // TEST("(3,5,7)", r2);                     // 23
  // vec3<float> r3 = 2 + vf8;
  // TEST("(3,5,7)", r3);                     // 23
  // vec3<float> r4 = vf8 - vf8;
  // TEST("(0,0,0)", r4);                     // 25
  // vec3<float> r5 = vf8 - 2;
  // TEST("(-1,1,3)", r5);                    // 26
  // vec3<float> r6 = 2 -vf8;
  // TEST("(1,-1,-3)", r6);                   // 27
  // vec3<float> r7 = vf8 * (-1);
  // TEST("(-1,-3,-5)", r7);                  // 28
  // vec3<float> r8 = 2 * vf8;
  // TEST("(2,6,10)", r8);                    // 29
  // vec3<float> r9 = vec3<float>(3) * vf8;
  // TEST("(3,9,15)", r9);                    // 30
  // vec3<float> r10 = vf8 / 2;
  // TEST("(0.5,1.5,2.5)", r10);              // 31
  // vec3<float> r11 = 2 / vf8;
  // TEST("(2,0.666,0.4)", r11);              // 32
  // vec3<float> r12 = vf8 / vec3<float>(0.5);
  // TEST("(2,6,10)", r12);                   // 33
  // // // vec2<float> r13 = vf11_ / 0.0;
  // bool equal1 = vec3<float>(1,2,3) == vec3<float>(1,2,3);
  // bool nequal1 = vec3<float>(1,2,3) != vec3<float>(1,2,3);
  // bool equal2 = vec3<float>(1,2,3) == vec3<float>(0,2,3);
  // bool nequal2 = vec3<float>(1,2,3) != vec3<float>(0,2,3);
  // TEST("1", equal1);                       // 34
  // TEST("0", nequal1);                      // 35
  // TEST("0", equal2);                       // 36
  // TEST("1", nequal2);                      // 37
  // float r14 = dot(vec3<float>(1,2,3), vec3<float>(2,3,4));
  // float r15 = vec3<float>(1,2,3).dot(vec3<float>(2,3,4));
  // TEST("20", r14);                         // 38
  // TEST("20", r15);                         // 39
  // vec3<float> r16 = vec3<float>(1,2,3)^vec3<float>(2,3,4);
  // vec3<float> r17 = cross(vec3<float>(1,2,3),vec3<float>(2,3,4));
  // vec3<float> r18 = vec3<float>(1,2,3).cross(vec3<float>(2,3,4));
  // TEST("(-1,2,-1)", r16);                  // 40
  // TEST("(-1,2,-1)", r17);                  // 41
  // TEST("(-1,2,-1)", r18);                  // 42

  // LOG("Length Testing!");
  // double l2 = vec3<float>(0,3,4).lengthSq();
  // double l = vec3<float>(0,3,4).length();
  // TEST("25", l2);                          // 43
  // TEST("5", l);                            // 44

  // LOG("Distance Testing!");
  // double d2 = distSq(vec3<float>(1,2,3), vec3<float>(1,1,2));
  // double d = dist(vec3<float>(1,2,3), vec3<float>(1,1,2));
  // TEST("2", d2);                            // 45
  // TEST("1.414", d);                         // 46

  // LOG("Normalize Testing!");
  // vec3<float> n(0,3,4);
  // vec3<float> gn = vec3<float>(0,3,4).getNormalize();
  // n.normalize();
  // TEST("(0,0.6,0.8)", n);                   // 47
  // TEST("(0,0.6,0.8)", gn);                  // 48

  // // LOG("<< / >> Testing!");
  // // vec2<float> r;
  // // // std::cin >> r;                       // TODO
  // // std::cout << r << std::endl;

  // LOG("Math Testing!");
  // vec3<float> r19 = min(vec3<float>(1,4,3), vec3<float>(2,3,1));
  // vec3<float> r20 = min(vec3<float>(1,3,2), 2);
  // TEST("(1,3,1)", r19);                     // 49
  // TEST("(1,2,2)", r20);                     // 50
  // vec3<float> r21 = max(vec3<float>(1,4,3), vec3<float>(2,3,5));
  // vec3<float> r22 = max(2, vec3<float>(1,4,-1));
  // TEST("(2,4,5)", r21);                     // 51
  // TEST("(2,4,2)", r22);                     // 52
  // vec3<float> abs_ = abs(vec3<float>(-2,1,-3));
  // TEST("(2,1,3)", abs_);                    // 53
  // vec3<int> floor_ = floor(vec3<float>(2.6,3.1,3.1));
  // vec3<int> ceil_ = ceil(vec3<float>(2.6,3.1,3.1));
  // vec3<int> round_ = round(vec3<float>(2.6,3.1,3.1));
  // TEST("(2,3,3)", floor_);                  // 54
  // TEST("(3,4,4)", ceil_);                   // 55
  // TEST("(3,3,3)", round_);                  // 56
  // vec3<float> frac_ = frac(vec3<float>(2.6,3.1,3));
  // TEST("(0.6,0.1,0)", frac_);               // 57
  // vec3<float> v1;
  // vec3<float> v2 = v1 + 0.00001;
  // vec3<float> v3 = v1 + 0.0000001;
  // TEST("0", floatEqual(v1, v2));            // 58
  // TEST("1", floatEqual(v1, v3));            // 53

  // SEP();
  // SEP();

  // **************************************************************************
// ******************************   Vec4   **********************************
// **************************************************************************


  // LOG("Start Testing vec4!");
  // SEP();

  // LOG("Static function Testing!");
  // TEST("(0,0,0,0)", vec4i::zeros());         // 0
  // TEST("(1,1,1,1)", vec4i::ones());          // 1

  // LOG("Constructor Testing!");
  // vec4<int> vi1;
  // TEST("(0,0,0,0)", vi1);                    // 2
  // vec4<int> vi2(1);
  // TEST("(1,1,1,1)", vi2);                    // 3
  // vec4<float> vf3(1, 2, 3, 4);
  // TEST("(1,2,3,4)", vf3);                    // 4
  // vec4<double> vd4(vi1.toType<double>().getData());
  // TEST("(0,0,0,0)", vd4);                    // 5
  // vec4<float> vf3_(vf3);
  // TEST("(1,2,3,4)", vf3_);                   // 6
  // vec4<float> vf5(vec3<float>(1,1,1),2);
  // TEST("(1,1,1,2)", vf5);                    // 7

  // LOG("Operator Testing!");
  // TEST(1, vf3[0]);                           // 8
  // TEST(2, vf3[1]);                           // 9
  // // TEST("wrong!", vf3[4]);
  // vf3[0] = 4;
  // TEST("(4,2,3,4)", vf3);                    // 10
  // vec4<float> vf6 = vi1.toType<float>();
  // TEST("(0,0,0,0)", vf6);                    // 11
  // vec4<float> vf7 = 3;
  // TEST("(3,3,3,3)", vf7);                    // 12
  // TEST("(-3,-3,-3,-3)", -vf7);               // 13
  // vec4<float> vf8(1,2,3,4);
  // vf8 += 1;
  // TEST("(2,3,4,5)", vf8);                    // 14
  // vf8 += vf8;
  // TEST("(4,6,8,10)", vf8);                   // 15
  // vf8 -= 2;
  // TEST("(2,4,6,8)", vf8);                    // 16
  // vf8 -= vec4<float>(1);
  // TEST("(1,3,5,7)", vf8);                    // 17
  // vf8 *= 2;
  // TEST("(2,6,10,14)", vf8);                  // 18
  // vf8 *= vec4<float>(2);
  // TEST("(4,12,20,28)", vf8);                 // 19
  // vf8 /= 2;
  // TEST("(2,6,10,14)", vf8);                  // 20
  // vf8 /= vec4<float>(2);
  // TEST("(1,3,5,7)", vf8);                    // 21
  // vec4<float> r1 = vf8 + vf8;
  // TEST("(2,6,10,14)", r1);                   // 22
  // vec4<float> r2 = vf8 + 2;
  // TEST("(3,5,7,9)", r2);                     // 23
  // vec4<float> r3 = 2 + vf8;
  // TEST("(3,5,7,9)", r3);                     // 23
  // vec4<float> r4 = vf8 - vf8;
  // TEST("(0,0,0,0)", r4);                     // 25
  // vec4<float> r5 = vf8 - 2;
  // TEST("(-1,1,3,5)", r5);                    // 26
  // vec4<float> r6 = 2 -vf8;
  // TEST("(1,-1,-3,-5)", r6);                  // 27
  // vec4<float> r7 = vf8 * (-1);
  // TEST("(-1,-3,-5,-7)", r7);                 // 28
  // vec4<float> r8 = 2 * vf8;
  // TEST("(2,6,10,14)", r8);                   // 29
  // vec4<float> r9 = vec4<float>(3) * vf8;
  // TEST("(3,9,15,21)", r9);                   // 30
  // vec4<float> r10 = vf8 / 2;
  // TEST("(0.5,1.5,2.5,3.5)", r10);            // 31
  // vec4<float> r11 = 2 / vf8;
  // TEST("(2,0.666,0.4,0.28)", r11);           // 32
  // vec4<float> r12 = vf8 / vec4<float>(0.5);
  // TEST("(2,6,10,14)", r12);                  // 33
  // // // // vec2<float> r13 = vf11_ / 0.0;
  // bool equal1 = vec4<float>(1,2,3,0) == vec4<float>(1,2,3,0);
  // bool nequal1 = vec4<float>(1,2,3,0) != vec4<float>(1,2,3,0);
  // bool equal2 = vec4<float>(1,2,3,0) == vec4<float>(0,2,3,0);
  // bool nequal2 = vec4<float>(1,2,3,0) != vec4<float>(0,2,3,0);
  // TEST("1", equal1);                         // 34
  // TEST("0", nequal1);                        // 35
  // TEST("0", equal2);                         // 36
  // TEST("1", nequal2);                        // 37
  // float r14 = dot(vec4<float>(1,2,3,0), vec4<float>(2,3,4,0));
  // float r15 = vec4<float>(1,2,3,0).dot(vec4<float>(2,3,4,0));
  // TEST("20", r14);                           // 38
  // TEST("20", r15);                           // 39
  // vec4<float> r16 = vec4<float>(1,2,3,4)^vec4<float>(2,3,4,5);
  // vec4<float> r17 = cross(vec4<float>(1,2,3,4),vec4<float>(2,3,4,5));
  // vec4<float> r18 = vec4<float>(1,2,3,4).cross(vec4<float>(2,3,4,5));
  // TEST("(-1,2,-1,1)", r16);                  // 40
  // TEST("(-1,2,-1,1)", r17);                  // 41
  // TEST("(-1,2,-1,1)", r18);                  // 42

  // LOG("Length Testing!");
  // double l2 = vec4<float>(0,3,4,0).lengthSq();
  // double l = vec4<float>(0,3,4,0).length();
  // TEST("25", l2);                            // 43
  // TEST("5", l);                              // 44

  // LOG("Distance Testing!");
  // double d2 = distSq(vec4<float>(1,2,3,4), vec4<float>(1,1,2,4));
  // double d = dist(vec4<float>(1,2,3,4), vec4<float>(1,1,2,4));
  // TEST("2", d2);                             // 45
  // TEST("1.414", d);                          // 46

  // LOG("Normalize Testing!");
  // vec4<float> n(0,3,4,0);
  // vec4<float> gn = vec4<float>(0,3,4,0).getNormalize();
  // n.normalize();
  // TEST("(0,0.6,0.8,0)", n);                   // 47
  // TEST("(0,0.6,0.8,0)", gn);                  // 48

  // // LOG("<< / >> Testing!");
  // // vec2<float> r;
  // // // std::cin >> r;                       // TODO
  // // std::cout << r << std::endl;

  // LOG("Math Testing!");
  // vec4<float> r19 = min(vec4<float>(1,4,3,1), vec4<float>(2,3,1,2));
  // vec4<float> r20 = min(vec4<float>(1,3,2,3), 2);
  // TEST("(1,3,1,1)", r19);                     // 49
  // TEST("(1,2,2,2)", r20);                     // 50
  // vec4<float> r21 = max(vec4<float>(1,4,3,3), vec4<float>(2,3,5,6));
  // vec4<float> r22 = max(2, vec4<float>(1,4,-1,3));
  // TEST("(2,4,5,6)", r21);                     // 51
  // TEST("(2,4,2,3)", r22);                     // 52
  // vec4<float> abs_ = abs(vec4<float>(-2,1,-3,-2));
  // TEST("(2,1,3,2)", abs_);                    // 53
  // vec4<int> floor_ = floor(vec4<float>(2.6,3.1,3.1,2.6));
  // vec4<int> ceil_ = ceil(vec4<float>(2.6,3.1,3.1,2.6));
  // vec4<int> round_ = round(vec4<float>(2.6,3.1,3.1,2.6));
  // TEST("(2,3,3,2)", floor_);                  // 54
  // TEST("(3,4,4,3)", ceil_);                   // 55
  // TEST("(3,3,3,3)", round_);                  // 56
  // vec4<float> frac_ = frac(vec4<float>(2.6,3.1,3,2.6));
  // TEST("(0.6,0.1,0,0.6)", frac_);             // 57
  // vec4<float> v1;
  // vec4<float> v2 = v1 + 0.00001;
  // vec4<float> v3 = v1 + 0.0000001;
  // TEST("0", floatEqual(v1, v2));              // 58
  // TEST("1", floatEqual(v1, v3));              // 53

  // SEP();
  // SEP();


  return 0;
}
