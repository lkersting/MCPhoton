SET(
  HEADERS ${HEADERS}
  Interpolate.hpp
  KNRej.hpp
  KNLinRej.hpp
  ComptonScatter.hpp
  AzimuthalRej.hpp
  ComptonScatter.hpp
  PhotonTransport.hpp
  PhotonScatter.hpp
  MCPhoton.hpp
  )

SET(CMAKE_CXX_FLAGS
-std=c++11
)

SET(
  SOURCES ${SOURCES}
  Interpolate.cpp
  KNRej.cpp
  KNLinRej.cpp
  AzimuthalRej.cpp
  PhotonTransport.cpp
)

ADD_LIBRARY(
  Lin
  MCPhoton.cpp
  ComptonScatter.cpp
)

TARGET_COMPILE_DEFINITIONS(
  Lin
  PRIVATE
  _INTERPOLATOR3=getLinearInterpolation3
  _INTERPOLATOR2=getLinearInterpolation2
)

ADD_LIBRARY(
  Log
  MCPhoton.cpp
  ComptonScatter.cpp
)

TARGET_COMPILE_DEFINITIONS(
  Log
  PRIVATE
  _INTERPOLATOR3=getLogInterpolation3
  _INTERPOLATOR2=getLogInterpolation2
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
  Constant_Lin
  ${SOURCES}
  )

TARGET_LINK_LIBRARIES(
  Constant_Lin
  Lin
  Constant
)

ADD_EXECUTABLE(
  Constant_Log
  ${SOURCES}
  )

TARGET_LINK_LIBRARIES(
  Constant_Log
  Log
  Constant
)

ADD_EXECUTABLE(
  Linear_Lin
  ${SOURCES}
  )

TARGET_LINK_LIBRARIES(
  Linear_Lin
  Lin
  Linear
)

ADD_EXECUTABLE(
  Linear_Log
  ${SOURCES}
  )

TARGET_LINK_LIBRARIES(
  Linear_Log
  Log
  Linear
)

ADD_EXECUTABLE(
  TwoPath_Lin
  ${SOURCES}
  )

TARGET_LINK_LIBRARIES(
  TwoPath_Lin
  Lin
  TwoPath
)

ADD_EXECUTABLE(
  TwoPath_Log
  ${SOURCES}
  )

TARGET_LINK_LIBRARIES(
  TwoPath_Log
  Log
  TwoPath
)

SET_TARGET_PROPERTIES( 
Constant_Lin
Constant_Log
Linear_Lin
Linear_Log
TwoPath_Lin
TwoPath_Log
PROPERTIES
OUTPUT_NAME "MCPhoton"
)

