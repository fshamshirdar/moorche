# Moorche

* libstage as a library and cpp as the programming language.
  - follow installation steps in https://github.com/rtv/Stage
  - sudo apt-get install qmake
  - set include and library paths in moorche.pro file
  - mkdir build
  - cd build
  - qmake ..
  - make

* similar to SO-LOST algorithm.
* trail is a set of points.
* points of the trails every n=10 cycles.
* there are 2 kinds of trails, one for moving from source to sink and one for reverse. -> in order to obstacle avoidance 
* each point of the trail has the following variables:
  - pose (x, y, alpha)
  - density (0.0 to 1.0) -> decreases frequently every cycle
  - creation cycle
  - distance to target
  - to-source or to-sink

* points of the trail are evaporated per cycle. -> has a parameter for controlling
* each robot search for the points of the trail in a specific radius=1.5 which has the best score (minimum distance)
* randomness parameter for following trail or walking around randomly.
* obstacle avoidance -> affect both random movement and following trail.
* finind situable parameters, obstacle avoidance and avoid sticking together were the most challenging part.
