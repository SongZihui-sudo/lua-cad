# 配置dealii

- [配置dealii](#配置dealii)
  - [具体流程](#具体流程)

## 具体流程

[Dealii安装说明](https://www.dealii.org/current/readme.html)

按照前面的安装说明，基本可以直接编译成功 dealii，但是过程会很慢。编译成功后会在安装的库的文件的 `lib` 目录里会出现几个动态链接库。在编译自己的程序时链接上就可以了。  

我在 xmake 中的配置:

```lua
add_includedirs("/home/songzihui/dealii-9.5.2/dealii_lib/include/")
add_linkdirs("/home/songzihui/dealii-9.5.2/dealii_lib/lib/")
add_links("libdeal_II.so")
```

**如果编译成功后程序运行出现找不到动态链接库的情况。**  
可以在 `/etc/ld.so.conf` 文件里加上库路径。  
在 `ldconfig` 即可。  

[解决方式](https://blog.csdn.net/qc530167365/article/details/91491851)  