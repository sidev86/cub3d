<h1>cub3D</h1>

<h2>Description</h2>

cub3D is a project inspired by the iconic video game Wolfenstein 3D. The goal is to recreate a similar scenario, featuring a realistic 3D representation of a maze from a first-person perspective. This is achieved using ray-casting techniques and the MiniLibX graphics library (a small graphics library, developed by 42). The project includes textured walls, customizable floor and ceiling colors, and smooth navigation, offering an immersive experience.


<h2>Features</h2>

<ul>
  <li><strong>Ray-Casting Engine:</strong> The 3D rendering technique used for this project, also used in 'Wolfenstein 3D' game.</li>
  <li><strong>Textured Walls:</strong> Supports different textures for walls based on their orientation (North, South, East, West).</li>
  <li><strong>Floor/Ceiling Colors:</strong> Configurable via RGB values.</li>
  <li><strong>Smooth Navigation:</strong> Player can rotate the view, and moving in all directions into the 3D scene.</li>
  <li><strong>Scene Files: </strong>The program accepts <code>.cub</code> files defining wall textures, floor and ceiling colors and the map layout with player starting position and orientation.</li>
  <li><strong>Wall collisions:</strong> Collision detection of player with map walls.</li>
  
</ul>


<h2><code>.cub</code> Scene File</h2>

A <code>.cub</code> file must contain the following elements:

<ul>
  <li><strong>Wall Textures</strong> Paths to texture files for each direction:</li>
    <ul>
      <li>NO (North)</li>
      <li>SO (South)</li>
      <li>WE (West)</li>
      <li>EA (East)</li> 
    </ul>
</ul>
 
