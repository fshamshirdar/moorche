# Moorche

Implementation of LOST (Localization-space trails for robot teams) in Stage. LOST is a multi-agent navigation algorithm that not only resolves the divergance issue of odometry but also converges that trail to be the shortest regarding the cost function.

* libstage as a library and cpp as the programming language.
  - follow installation steps in https://github.com/rtv/Stage
  - sudo apt-get install qmake
  - set include and library paths in moorche.pro file
  - mkdir build
  - cd build
  - qmake ..
  - make
  - ./moorche ../worlds/simple.world 7
