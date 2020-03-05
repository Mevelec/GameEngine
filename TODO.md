[ ] 1. find a way to invert the display of chunk manager on x 

[x] 2. complete chunk controller
[x] 	- inffer chunk pos from the manager ? yes or no ? => not before creating dynamic load
[x] 	- add menu to mgui for chunkManager
[x] 	- expose controlls to edit chunkManager parameters

[x] 3. block Manager
[x]	- use block manager to save block instance and share them
[ ]	- optimize create when not existing ( separate create a new blocktype and create a new sdtate)

[ ] 4. update chunk
[ ] - create generate() : genereate octree content
[ ] - create load()     : set visibilities inside octree
[ ] - create build()    : create VA
[ ] - create optimized reload()     : set visibilities inside octree and generate VA at the same time (on loob for the two)

[x]	- add visible and active bool to blocks
[ ]	- add function to get neightboor Block ( with optional load from neightboor chunk ) by defaul if get out of bound return to display
[ ]	- use visible to generate chunk VA ( to not generate hiden blocks)
[ ] - do not display hiden faces of blocks