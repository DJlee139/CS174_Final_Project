all: everything 

everything: Camera.o Cube.o Mesh.o MeshMakers.o Sphere.o  Thing.o  Wall.o World.o main.o Circle.o InitShader.o Bullet.o
	g++ ./Camera.o ./Cube.o ./Mesh.o ./MeshMakers.o ./Sphere.o ./Thing.o ./InitShader.o  ./Wall.o ./World.o ./main.o ./Circle.o ./Bullet.o -o final -lGL -lGLU -lglut -lGLEW


Bullet.o: Bullet.cpp
	g++ -c -w -g -DDEBUG -DLINUX ./Bullet.cpp -o ./Bullet.o

InitShader.o: InitShader.cpp
	g++ -c -w -g -DDEBUG -DLINUX ./InitShader.cpp -o ./InitShader.o
Circle.o: Circle.cpp
	g++ -c -w -g -DDEBUG -DLINUX ./Circle.cpp -o ./Circle.o
Camera.o: Camera.cpp
	g++ -c -w -g -DDEBUG -DLINUX ./Camera.cpp -o ./Camera.o
Cube.o: Cube.cpp
	g++ -c -w -g -DDEBUG -DLINUX ./Cube.cpp -o ./Cube.o
Mesh.o:Mesh.cpp
	g++ -c -w -g -DDEBUG -DLINUX ./Mesh.cpp -o ./Mesh.o
MeshMakers.o: MeshMakers.cpp
	g++ -c -w -g -DDEBUG -DLINUX ./MeshMakers.cpp -o ./MeshMakers.o

Sphere.o: Sphere.cpp
	g++ -c -w -g -DDEBUG -DLINUX ./Sphere.cpp -o ./Sphere.o

Thing.o:Thing.cpp
	g++ -c -w -g -DDEBUG -DLINUX ./Thing.cpp -o ./Thing.o



Wall.o: Wall.cpp
	g++ -c -w -g -DDEBUG -DLINUX ./Wall.cpp -o ./Wall.o
World.o: World.cpp
	g++ -c -w -g -DDEBUG -DLINUX ./World.cpp -o ./World.o
main.o: main.cpp
	g++ -c -w -g -DDEBUG -DLINUX ./main.cpp -o ./main.o


clean:
	rm -f ./*.o
	rm -f final
