file = "imageData.h"
fi = io.open(file,"r")
str = fi:read("*all")

str = string.gsub(str,"(%w+)_WIDTH","WIDTH_%1")
str = string.gsub(str,"(%w+)_HEIGHT","HEIGHT_%1")

fi:close()

fo = io.open("output.txt","w")
fo:write(str)

fo:close()
