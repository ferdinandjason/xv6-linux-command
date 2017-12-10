# FPE8-SistemOperasi

Final Project Operating System :
- Make CLI in xv6 
- Using Primitive C :(
- xv6 MIT : https://github.com/NewbiZ/xv6


Command | Option | Status | Bug
--------|--------|--------|-------
`cp`  | `default` </br></br> `-R` </br> `*` |  :heavy_check_mark: </br></br>  :heavy_check_mark: </br>  :heavy_check_mark: | file or directory inside the folder if more than 5 will crash / `no such file or directory`, maybe because limitation of memory </br></br> added *.(eks) option </br> 
`ls`  | `default` </br> `-l` </br> `-a` |  :heavy_check_mark: </br>  :heavy_check_mark: </br>  :heavy_check_mark: | bug with ls multiple option </br>  </br>
`mv`  | `default` </br> `*` |  :heavy_check_mark: </br>  :heavy_check_mark: | move folder (?) bug ;( </br> no *.(eks) option
`rm`  | `default` </br> `-rf` |  :heavy_check_mark: </br> :heavy_check_mark: |  file or directory inside the folder if more than 5 will crash / `no such file or directory`, maybe because limitation of memory </br>  
`cd`  | `default` |  :heavy_check_mark: | Bug comes with multiple change directory like ../../.. in `pwd` or `temp.pwd` will bug
`clear` | `default` |  :heavy_check_mark: | xv6 qemu terminal can't clear (should using '\n' multiple times) or -nox option will work
`rename`  |`default` </br> `-s` </br> `-v` </br> `-n` <br> `-o` |  :heavy_check_mark: </br>  :heavy_check_mark:  </br>  :heavy_check_mark: </br>  :heavy_check_mark: </br>  :heavy_check_mark: | rename to long extension to short extension -> like .txt to .c  </br> error in some case </br>  error in some case </br> error in some case </br> </br>
`pwd` | `default` </br> `-l` </br> `-p` |  :heavy_check_mark: <br>  :heavy_check_mark: </br>  :heavy_check_mark: | linear search within argument value where split by `/` <br> no symlink in xv6, `-l` and `-p` option will show the same value </br> </br>
`touch` | `default` |  :heavy_check_mark: | touch the samefile should be produce error (?)

Make By :
- Ferdinand Jason
- Nurlita Dhuha
- Alvin Tanuwijaya
- Bagus Aji Sinto
