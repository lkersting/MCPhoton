SET(DIRECTORY
  ${DIRECTORY}
  /home/lujoke/Documents/CPP
)

SET(HEADERS 
  ${HEADERS}
  Interpolate.hpp
  KNRej.hpp
  KNLinRej.hpp
  ComptonScatter.hpp
  AzimuthalRej.hpp
  PhotonTransport.hpp
  PhotonScatter.hpp
  MCPhoton.hpp
  )

SET(CMAKE_CXX_FLAGS 
  ${CMAKE_CXX_FLAGS}
  -std=c++11
)

SET(SOURCES 
  ${SOURCES}
  Interpolate.cpp
  KNRej.cpp
  KNLinRej.cpp
  AzimuthalRej.cpp
  PhotonTransport.cpp
)

ADD_LIBRARY(
  Lin
  MCPhoton.cpp
)

TARGET_COMPILE_DEFINITIONS(
  Lin
  PRIVATE
  _INTERPOLATOR3=getLinearInterpolation3
  DIR=${DIRECTORY}
)

ADD_LIBRARY(
  Log
  MCPhoton.cpp
)

TARGET_COMPILE_DEFINITIONS(
  Log
  PRIVATE
  _INTERPOLATOR3=getLogInterpolation3
  DIR=/home/lujoke/Documents/CPP/MCPhoton/data
)

ADD_LIBRARY(
  Constant
  PhotonScatter.cpp
)

TARGET_COMPILE_DEFINITIONS(
  Constant
  PRIVATE
  MU_REJECTION_SAMPLING=KNRej
)

ADD_LIBRARY(
  Linear
  PhotonScatter.cpp
)

TARGET_COMPILE_DEFINITIONS(
  Linear
  PRIVATE
  MU_REJECTION_SAMPLING=KNLinRej
)

ADD_LIBRARY(
  TwoPath
  PhotonScatter.cpp
)

TARGET_COMPILE_DEFINITIONS(
  TwoPath
  PRIVATE
  MU_REJECTION_SAMPLING=ComptonScatter
)
   
ADD_EXECUTABLE(
  constant_lin
  ${SOURCES}
  )

TARGET_LINK_LIBRARIES(
  constant_lin
  Lin
  Constant
)

ADD_EXECUTABLE(
  constant_log
  ${SOURCES}
  )

TARGET_LINK_LIBRARIES(
  constant_log
  Log
  Constant
)

ADD_EXECUTABLE(
  linear_lin
  ${SOURCES}
  )

TARGET_LINK_LIBRARIES(
  linear_lin
  Lin
  Linear
)

ADD_EXECUTABLE(
  linear_log
  ${SOURCES}
  )

TARGET_LINK_LIBRARIES(
  linear_log
  Log
  Linear
)

ADD_EXECUTABLE(
  twopath_lin
  ${SOURCES}
  ComptonScatter.cpp
  )

TARGET_LINK_LIBRARIES(
  twopath_lin
  Lin
  TwoPath
)

ADD_EXECUTABLE(
  twopath_log
  ${SOURCES}
  ComptonScatter.cpp
  )


TARGET_LINK_LIBRARIES(
  twopath_log
  Log
  TwoPath
)

SET_TARGET_PROPERTIES( 
constant_lin
constant_log
linear_lin
linear_log
twopath_lin
twopath_log
PROPERTIES
OUTPUT_NAME "MCPhoton"
COMPILE_DEFINITIONS
DIR=${DIRECTORY}
)

TARGET_COMPILE_DEFINITIONS(
  twopath_lin
  PRIVATE
  "_INTERPOLATOR2=getLinearInterpolation2"
)

TARGET_COMPILE_DEFINITIONS(
  twopath_log
  PRIVATE
  "_INTERPOLATOR2=getLogInterpolation2"
)

