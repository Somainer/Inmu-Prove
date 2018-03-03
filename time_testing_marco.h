//
// Created by somai on 2018/3/3.
//

#ifndef INMU_PROVE_TIME_TESTING_MARCO_H
#define INMU_PROVE_TIME_TESTING_MARCO_H
int _Main(int, char**);
#define main(...) \
  main(int argc, char** argv) { \
    auto _s = clock();\
    auto _r = _Main(argc, argv); \
    printf("\nFinished in %d ms.\n", 1000*(clock()-_s)/CLOCKS_PER_SEC);\
    return _r;\
  }; \
  int _Main(__VA_ARGS__)
#endif //INMU_PROVE_TIME_TESTING_MARCO_H
