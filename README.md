<h1>cub3D</h1>

<h2>Description</h2>

cub3D is a project inspired by the iconic videogame Wolfenstein 3D. The goal is to recreate a similar scenario, featuring a realistic 3D representation of a maze from a first-person perspective. This is achieved using ray-casting techniques and the MiniLibX graphics library (a small graphics library, developed by 42). The project includes textured walls, customizable floor and ceiling colors, and smooth navigation, offering an immersive experience.

<br>
<h2>Features</h2>

<ul>
  <li><strong>Ray-Casting Engine:</strong> The 3D rendering technique used for this project, also used in 'Wolfenstein 3D' game.</li>
  <li><strong>Textured Walls:</strong> Supports different textures for walls based on their orientation (North, South, East, West).</li>
  <li><strong>Floor/Ceiling Colors:</strong> Configurable via RGB values.</li>
  <li><strong>Smooth Navigation:</strong> Player can rotate the view, and moving in all directions into the 3D scene.</li>
  <li><strong>Scene Files: </strong>The program accepts <code>.cub</code> files defining wall textures, floor and ceiling colors and the map layout with player starting position and orientation.</li>
  <li><strong>Wall collisions:</strong> Collision detection of player with map walls.</li>
  
</ul>

<br>
<h2><code>.cub</code> Scene File</h2>

<p>A <code>.cub</code> file must contain the following elements:</p>
<ol>
  <li><strong>Wall Textures</strong>: Paths to texture files for each direction:
    <ul>
      <li><code>NO</code> (North)</li> 
      <li><code>SO</code> (South)</li> 
      <li><code>WE</code> (West)</li> 
      <li><code>EA</code> (East)</li>
    </ul>
  </li>
  <li><strong>Floor and Ceiling Colors</strong> (RGB values):
    <ul>
      <li><code>F 220,100,0</code> (e.g for floor)</li>
      <li><code>C 225,30,0</code> (e.g for ceiling)</li>
    </ul>
  </li>
  <li><strong>Maze Layout</strong>:
    <ul>
      <li><code>0</code> for empty spaces.</li>
      <li><code>1</code> for walls.</li>
      <li><code>N</code>, <code>S</code>, <code>E</code>, or <code>W</code> for the player’s starting position and orientation.</li>
    </ul>
  </li>
  <li><strong>Rules</strong>:
    <ul>
      <li>The maze must be surrounded by walls.</li>
      <li>Elements must follow the specified format but can be separated by blank lines.</li>
      <li>Spaces are valid within the map layout and must be handled appropriately.</li>
    </ul>
  </li>
</ol>
<br>
<p>Example <code>.cub</code> file:</p>
<pre>
NO ./textures/north_texture.xpm
SO ./textures/south_texture.xpm
WE ./textures/west_texture.xpm
EA ./textures/east_texture.xpm
<br>  
F 220,100,0
C 225,30,0
<br>
111111
100101
101001
1100N1
111111
</pre>
<br>
<h2>Controls</h2>

<table>
    <thead>
      <tr>
        <th>Action</th>
        <th>Key Control</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td>Move Forward</td>
        <td>W</td>
      </tr>
      <tr>
        <td>Move Backward</td>
        <td>S</td>
      </tr>
      <tr>
        <td>Move Left</td>
        <td>A</td>
      </tr>
      <tr>
        <td>Move Right</td>
        <td>D</td>
      </tr>
      <tr>
        <td>Rotate Left</td>
        <td>Left Arrow</td>
      </tr>
      <tr>
        <td>Rotate Right</td>
        <td>Right Arrow</td>
      </tr>
      <tr>
        <td>Exit Program</td>
        <td>ESC</td>
      </tr>
    </tbody>
</table>
  
<br>
<h2>Map Error Handling</h2>
<p>The program exits with an error message in the following cases:</p>
<ul>
  <li>Misconfigured <code>.cub</code> file.</li>
  <li>Invalid maze layout or missing required elements (texture or floor/ceil color).</li>
  <li>File I/O issues.</li>
</ul>

 <h2>Compilation Instructions (linux systems)</h2>
  <ul>
    <li>Type <strong><code>make</code></strong> to generate the  <strong><code>cub3D</code></strong> executable file</li>
  </ul>
 <h2>Usage</h2>
   <li>After compiling, execute the program by passing the path to the <strong><code>.cub</code></strong> map file as an argument. For example:</li>
    <pre><code>./cub3D path/to/your_map_file.cub</code></pre>

<strong>Readme WIP ....</strong>
 
