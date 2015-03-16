build :
	g++ -o main main.cpp FrameBuffer.cpp Point.cpp Polygon.cpp Rect.cpp
keyboard :
	g++ -o mKeyboard mKeyboard.cpp keyboard.cpp FrameBuffer.cpp Point.cpp Polygon.cpp Rect.cpp
mouse : 
	g++ -o mMouse mMouse.cpp Mouse.cpp FrameBuffer.cpp Point.cpp Polygon.cpp Rect.cpp
object3d :
	g++ -o mObject3D mObject3D.cpp Object3D.cpp FrameBuffer.cpp Point.cpp Polygon.cpp Rect.cpp Vertex.cpp
projection :
	g++ -o mProjection mProjection.cpp Projection.cpp FrameBuffer.cpp Point.cpp Polygon.cpp
3dmap :
	g++ -o m3dmap m3dmap.cpp FrameBuffer.cpp Point.cpp Polygon.cpp Keyboard.cpp
tubes :
	g++ -o mTubes mTubes.cpp FrameBuffer.cpp Point.cpp Polygon.cpp Rect.cpp Keyboard.cpp Mouse.cpp
tugas2 :
	g++ -o maintes maintes.cpp Pesawat.cpp Kapal.cpp Peluru.cpp Ledakan.cpp Parabola.cpp Parasut.cpp FrameBuffer.cpp Point.cpp Polygon.cpp MovingObject.cpp
