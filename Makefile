build :
	g++ -o main main.cpp FrameBuffer.cpp Point.cpp Polygon.cpp Rect.cpp Ship.cpp
keyboard :
	g++ -o mKeyboard mKeyboard.cpp keyboard.cpp FrameBuffer.cpp Point.cpp Polygon.cpp Rect.cpp
mouse : 
	g++ -o mMouse mMouse.cpp Mouse.cpp FrameBuffer.cpp Point.cpp Polygon.cpp Rect.cpp
object3d :
	g++ -o mObject3D mObject3D.cpp Object3D.cpp FrameBuffer.cpp Point.cpp Polygon.cpp Rect.cpp Vertex.cpp