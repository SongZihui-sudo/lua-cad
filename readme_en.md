# lua-cad

OpenSCAD for Lua, uses lua to create 3D models.

<!-- PROJECT SHIELDS -->

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![GPLv3 License][license-shield]][license-url]


<!-- PROJECT LOGO -->
<br />

<p align="center">
   <a href="https://github.com/SongZihui-sudo/lua-cad/">
     <img src="https://lua.org/images/lua30.gif" alt="Logo" width="200" height="200">
   </a>

   <h3 align="center">Lua-cad</h3>
   <p align="center">
     OpenSCAD for Lua, use lua to quickly create 3D models.
     <br />
     <a href="./doc/index.md"><strong>Explore this project's documentation »</strong></a>
     <br />
     <br />
     <a href = "https://github.com/SongZihui-sudo/lua-cad/issues/new">Report a Bug</a>
     ·
     <a href="https://github.com/SongZihui-sudo/lua-cad/issues">Propose new features</a>
     ·
     <a href="./readme_en.md">English</a>
   </p>

</p>
 
## Table of contents

- [lua-cad](#lua-cad)
  - [Table of contents](#table-of-contents)
    - [**Features**](#features)
      - [**Use datums to achieve accurate positioning**](#use-datums-to-achieve-accurate-positioning)
      - [**Fast transplantation, reuse of existing code, compatible with openscad’s module calling statements**](#fast-transplantation-reuse-of-existing-code-compatible-with-openscads-module-calling-statements)
      - [**Object-oriented**](#object-oriented)
    - [Example](#example)
        - [Simple centrifugal fan housing](#simple-centrifugal-fan-housing)
        - [Reuse openscad](#reuse-openscad)
        - [Basic operations](#basic-operations)
    - [document](#document)
    - [Getting Started Guide](#getting-started-guide)
          - [**Source code compilation**](#source-code-compilation)
        - [**Instructions for use**](#instructions-for-use)
    - [Architecture diagram](#architecture-diagram)
    - [File directory description](#file-directory-description)
    - [Open source projects used](#open-source-projects-used)
    - [Contributors](#contributors)
      - [How to participate in open source projects](#how-to-participate-in-open-source-projects)
    - [version control](#version-control)
    - [author](#author)
    - [Copyright statement](#copyright-statement)
    - [Acknowledgments](#acknowledgments)

### **Features**

#### **Use datums to achieve accurate positioning**

Using `datum` in lua-cad can accurately determine the datum plane of 3D objects, so as to achieve accurate positioning based on the geometric relationship between objects.
```lua
local datum1 = d3object.datum(cube1, 1);
```
Use the `d3object.datum(obj, index)` function to obtain the position of the datum center, and use the `datum` library to process geometric relationships.

#### **Fast transplantation, reuse of existing code, compatible with openscad’s module calling statements**

Quickly reuse modules you create in `openscad` in lua-cad.
```lua
local shoulder_screw1 = $shoulder_screw( "english", 1/2, length = 20 )$;
```
Use `$` in Lua-cad to create the module you want to define in the openscad file, which will convert it into a variable of type `table`. In the `user_define_obj` library you can manipulate it further. [User-defined object library](./doc/userdefineobject.md).

#### **Object-oriented**

Adopting an object-oriented model, code can be reused efficiently, coding is more flexible, and maintainability is increased.

### Example

##### Simple centrifugal fan housing

[Example](./Example/fan_housing/fan_housing.lua)
![image1](./Example/fan_housing/export1.png)
![image2](./Example/fan_housing/export2.png)

##### Reuse openscad

```lua
-- The directory is specified according to the actual situation
package.path = package.path ..';../../../../?.lua';
user_obj = require("src.user_object.user_obj")

--test1
test1 = $shoulder_screw( "english", 1/2, length = 20 )$;

test1.postion(test1, {10, 10, 10});

print("offset");
print("x: ".. test1._offset[1]);
print("x: ".. test1._offset[2]);
print("x: ".. test1._offset[3]);
print("test1");
test1.print(test1);

--test2
test2 = $screw( "#6-32", head="flat undercut",length=12)$;
print("test2")
test2.print(test2);
```

##### Basic operations

```lua
d3object = require("d3object")
boolean = require("boolean")
transform = require("transform")

local cube1 = d3object.cube({ 10, 10, 10 }, true);
local cube2 = d3object.cube({ 10, 10, 10 }, false);

local difference1 = boolean.difference({cube1, cube2});
local difference2 = boolean.difference({difference1, cube1});
local difference3 = boolean.difference({cube1, cube2, difference2});
local union1 = boolean.union({difference1, difference2});
local intersection1 = boolean.intersection({union1, difference3});

print("difference1 code1 : \n" .. code(intersection1));

export("./export.scad", intersection1);
```

### document

[Detailed documentation](./doc/index.md)

### Getting Started Guide

###### **Source code compilation**

1. Install `xmake`
    - [xmake installation method](https://xmake.io/#/guide/installation)
2. Clone the repo
```sh
git clone https://github.com/SongZihui-sudo/lua-cad.git
```
3. cd lua-cad
4. Compile source code
```sh
xmake
```

##### **Instructions for use**

```sh
lua-cad [filepath]
```
If the parameter `filepath` is entered, the file pointed to by the script `filepath` is run directly. Otherwise the input is read from the terminal.
![read_line](./IMAGE/image.png)

### Architecture diagram

![Architecture Diagram](./IMAGE/Architecture.png)

### File directory description

eg:

```
filetree
├── doc
│ └── English
├── lua
│ ├── manual
│ └── tests
│ └── libs
│ └── P1
├── port
│ └── openscad
├── src
│ ├── base_object
│ └── user_object
└── test
```

/doc document.
/lua lua source code, individual files have been modified.
/port file export and rendering interface.
/src source code.
/src/base_object base object source code.
/src/user_object User-defined object source code.

### Open source projects used

- [lua](https://lua.org/)

### Contributors

#### How to participate in open source projects

Contributions make the open source community a great place to learn, inspire, and create. Any contribution you make is **very much appreciated**.


1. Fork the Project
2. Make some changes
3. Commit your Changes (`git commit -m 'Add some feature'`)
4. Push to the Branch to your repo (`git push`)
5. Open a Pull Request to `feature` Branch.

### version control

This project uses Git for version management. You can see the currently available versions in the repository.

### author

SongZihui-sudo

mail: 1751122876@qq.com


### Copyright statement

This project is licensed under GPLv3, please see [LICENSE.txt](./LICENSE.txt) for details

### Acknowledgments


- [lua](https://lua.org/)
- [openscad](https://openscad.org/index.html)

<!-- links -->
[your-project-path]:SongZihui-sudo/lua-cad
[contributors-shield]: https://img.shields.io/github/contributors/SongZihui-sudo/lua-cad.svg?style=flat-square
[contributors-url]: https://github.com/SongZihui-sudo/lua-cad/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/SongZihui-sudo/lua-cad.svg?style=flat-square
[forks-url]: https://github.com/SongZihui-sudo/lua-cad/network/members
[stars-shield]: https://img.shields.io/github/stars/SongZihui-sudo/lua-cad.svg?style=flat-square
[stars-url]: https://github.com/SongZihui-sudo/lua-cad/stargazers
[issues-shield]: https://img.shields.io/github/issues/SongZihui-sudo/lua-cad.svg?style=flat-square
[issues-url]: https://github.com/SongZihui-sudo/lua-cad/issues
[license-shield]: https://img.shields.io/github/license/SongZihui-sudo/lua-cad.svg?style=flat-square
[license-url]: ./LICENSE.txt

[![Star History Chart](https://api.star-history.com/svg?repos=SongZihui-sudo/lua-cad&type=Date)](https://star-history.com/#SongZihui-sudo/lua-cad&Date)  
