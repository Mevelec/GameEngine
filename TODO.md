## Upgrade of Chunk 1
[ ] 1. find a way to invert the display of chunk manager on x 

[x] 2. complete chunk controller
[x] 	- inffer chunk pos from the manager ? yes or no ? => not before creating dynamic load
[x] 	- add menu to mgui for chunkManager
[x] 	- expose controlls to edit chunkManager parameters

[x] 3. block Manager
[x]	- use block manager to save block instance and share them
[x]	- optimize create when not existing ( separate create a new blocktype and create a new state) => no because performance gain is small

[ ] 5. update geometry to load specified faces 

[ ] 4. update chunk
[x] - create generate() : genereate octree content
[x] - create load()     : set visibilities inside octree
[x] - create build()    : create VA
[ ] - create optimized reload()     : set visibilities inside octree and generate VA at the same time (on loob for the two)

[x]	- add visible and active bool to blocks
[x]	- use visible to generate chunk VA ( to not generate hiden blocks)

[ ] - correct error when a chunk is empty (no VA -> generating error)

## Upgrade of Chunk 2
[ ] 1. update geometry to load specified faces 

[ ] 2. update chunk
[ ] - update build()    : create VA using direction to display ( top, left ...) faces only
[ ] - create optimized reload()     : set visibilities inside octree and generate VA at the same time (on loob for the two)
