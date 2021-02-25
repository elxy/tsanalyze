# TS Analyze

use basic rules from ISO 13818 and ETSI EN 300 468 to decode MPEG2 TS

output PSI tables infomation

personal practice on ts decoding

# Compile

Two methods: start with 
```
- autogen.sh
- cmake 
```
and then do ```make``` for both

# Usage
```
./tsanalyze tsfile
```
```
options: -f [udp][file]   support file and udp stream analyze
options: -s [pat][cat][pmt][tsdt][nit][sdt][bat][tdt] output table selected
options: -o [stdout][txt][json] output to file or terminal format
```

# descriptor
not all descriptor implemented now, see ```doc/descriptor.md``` to add new descriptors