difference()
{
union()
{
cylinder(h = 15.000000, r = 20.000000,  center = false);
cube([30.000000, 20.000000, 15.000000], center = false);

}
cylinder(h = 12.000000, r = 17.000000,  center = false);
translate([0.000000, 0.000000, 12.000000])
cylinder(h = 10.000000, r = 5.000000,  center = false);
translate([0.000000, 3.000000, 3.000000])
cube([30.000000, 14.000000, 9.000000], center = false);

}
