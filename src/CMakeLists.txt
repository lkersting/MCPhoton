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

ADD_DEFINITIONS(
-std=c++11
)

SET(
	DEFINITION 
	-D_DIR="/home/lujoke/Documents/MCPhoton2/data"
)
 
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_INTERPOLATOR3=getLinearInterpolation3 -D_INTERPOLATOR2=getLinearInterpolation2 ${DEFINITION}"
)

ADD_EXECUTABLE(
  MCPhoton
  Interpolate.cpp
  KNRej.cpp
  KNLinRej.cpp
  ComptonScatter.cpp
  AzimuthalRej.cpp
  ComptonScatter.cpp
  PhotonTransport.cpp
  PhotonScatter.cpp
  MCPhoton.cpp
  )
