## Upgrade of Chunk 1
[ ] 1. find a way to invert the display of chunk manager on x 

[x] 2. complete chunk controller
[x] 	- inffer chunk pos from the manager ? yes or no ? => not before creating dynamic load
[x] 	- add menu to mgui for chunkManager
[x] 	- expose controlls to edit chunkManager parameters

[x] 3. block Manager
[x]		- use block manager to save block instance and share them
[x]		- optimize create when not existing ( separate create a new blocktype and create a new state) => no because performance gain is small

[x] 4. update chunk
[x]		- create generate() : genereate octree content
[x]		- create load()     : set visibilities inside octree
[x]		- create build()    : create VA
[x]		- create unload()

[x]		- add visible and active bool to blocks
[x]		- use visible to generate chunk VA ( to not generate hiden blocks)

[x]		- correct error when a chunk is empty (no VA -> generating error)

[x] 6. Add profiler to new functions

## Create Geometry Loader
[x] 1. implement loader OBJ
[x]     - add library 

[x] 2. update Geometry
[x]     - ability to  specify a layout
[x]     - offset indices ability to desactivate

[ ] 3. handle OBJ material 

[ ] 4. handle OBJ textures
[x]     - coordinates
[ }		- import map (texture)
[ ] 5. handle normals

## Upgrade of Chunk 2
[x] 1. update geometry to load specified faces 
[x]		- adapt geometry struct
[x]		- update loader to return Geometry ( use satic geo to buld) : create static geo and can add them to geometry
[x]		- create primitive Cube creation with specified faces

[ ] 2. update chunk
[x]     - update build()    : create VA using direction to display ( top, left ...) faces only
[ ]     - create optimized reload()     : set visibilities inside octree and generate VA at the same time (on loob for the two)
[ ]	    - create optimized rebuild()     : set visibilities inside octree and generate VA at the same time (on loob for the two)

[ ] 3. optimize chunkManager rendering (material load at each render of chunk is heavy)
[ ]     - use chunk visibility 
[x]     - static material lib
[x]     - better bind of materials
[x]     - better create lib of materials 

[ ] 4. better handle shaders
[ ]     - create a staic lib, connected to mateial lib
