package.path = package.path .. ';../../../../?.lua';
user_obj = require("src.user_object.user_obj");
chunk = require("src.chunk")
class = require("src.lua_class.class")

fan_housing = class();
function fan_housing:ctor(_wall_thickness)
    self.wall_thickness = _wall_thickness;
end

-- 主体
function fan_housing:bucket()
    self.bucket_info = {
        h = 15,
        r = 20
    };
    self.bucket = d3object.cylinder(self.bucket_info, false);
    self.cube1_info =
    {
        30,
        20,
        self.bucket_info.h
    }
    self.cube1 = d3object.cube(self.cube1_info, false);
    self.union1 = boolean.union({self.bucket, self.cube1});
end

-- 出风口
function fan_housing:air_outlet()
    local datum_bottom = d3object.datum(self.bucket, 2);
    self.cube2 = d3object.cube({self.cube1_info[1], self.bucket_info.r - self.wall_thickness * 2,
                                self.bucket_info.h - self.wall_thickness * 2}, false);
    datum_bottom = datum.relative(datum_bottom, "y", self.wall_thickness);
    datum_bottom = datum.relative(datum_bottom, "z", self.wall_thickness);
    transform.postion(self.cube2, datum.to_table(datum_bottom));
    return self.cube2;
end

-- 中间开洞
function fan_housing:hole()
    local hole1_info = {
        h = self.bucket_info.h - self.wall_thickness,
        r = self.bucket_info.r - self.wall_thickness
    };
    self.hole1 = d3object.cylinder(hole1_info, false);

    -- 确定顶部坐标
    local datum_top = d3object.datum(self.bucket, 1);
    datum_top = datum.relative(datum_top, "z", -self.wall_thickness);
    local small_hole_info = {
        h = 10,
        r = 5
    };
    self.small_hole = d3object.cylinder(small_hole_info, false);
    transform.postion(self.small_hole, datum.to_table(datum_top));
end

-- 代码导出
function fan_housing:output(filepath)
    local main_chunk = {};
    setmetatable(main_chunk, chunk);
    local difference1 = boolean.difference({self.union1, self.hole1, self.small_hole, self.cube2});
    table.insert(main_chunk, difference1);
    -- 代码导出
    local code = main_chunk.code(main_chunk);
    export(filepath, code);
    return code;
end

-- main
function main()
    -- 创建对象
    obj = fan_housing.new(3);
    obj:bucket();
    obj:air_outlet();
    obj:hole();
    obj:output("./export.scad");
end

main();
