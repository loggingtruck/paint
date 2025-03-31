<h1>Paint Application</h1>
<p>Instructions on how to compile and run the Paint application, a simple graphics application built with OpenGL, GLFW, and GLAD.</p>

<h1>Prerequisites</h1>
<p>Before compiling the app, the following must be installed:</p>

<ol> 
  <li>Git</li>
  <li>C compiler that supports C17/23 (GCC, Clang, etc.)</li>
  <li>CMake (optional but recommended)</li>
</ol>

<h2>Method 1: Using GCC Directly from Terminal (Windows Only)</h2>
<ol>
  <li>clone URL: https://github.com/loggingtruck/paint.git
  <pre><code> git clone https://github.com/loggingtruck/paint.git </code></pre></li>
  
  <li>Navigate to the paint folder:
    <pre><code>cd paint</code></pre>
  </li> 

  <li>Compile the program:
    <pre><code>gcc -std=c23 -o paint.exe src/*.c .\libraries\glad\src\glad.c -I.\header -I.\libraries\glad\include -I.\libraries\glfw\include -L.\libraries\glfw\lib -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32</code></pre>
    <p>Explanation of flags:</p>
    <ul> 
      <li><code>-std=c23</code>: Sets C language standard</li>
      <li><code>-o paint.exe</code>: Name of the executable file</li>
      <li><code>src/*.c</code>: Includes all C source files in the <code>src</code> directory</li>
      <li><code>-I</code>: Add directories to the include search path</li>
      <li><code>-L</code>: Add a directory to the library search path</li>
      <li><code>-l</code>: Link libraries</li>
    </ul>
  </li>

  <li>Run the application:
    <pre><code>.\paint.exe</code></pre>
  </li>
</ol>

<h2>Method 2: Using CMake from terminal (Cross-Platform)</h2>
<ol>
  <li>clone URL: https://github.com/loggingtruck/paint.git
  <pre><code> git clone https://github.com/loggingtruck/paint.git </code></pre></li>
  <li>Download CMake: <a href="https://cmake.org/download/">https://cmake.org/download/</a> and install it.</li>
  <li>Navigate to the paint folder:
    <pre><code>cd paint</code></pre>
  </li>
  
  <li>Create a build directory:
    <pre><code>mkdir build 
cd build</code></pre>
  </li>

  <li>Generate build files with CMake:
    <pre><code>cmake ..</code></pre>
  </li>

  <li>Build the project:
    <pre><code>cmake --build .</code></pre>
  </li>
</ol>

<h2>Running the Application</h2>

<h3>Windows:</h3>
<pre><code>.\paint.exe</code></pre>

<h3>Linux/macOS:</h3>
<pre><code>./paint</code></pre>
