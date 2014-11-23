import string

# Open a file
fo = open("versioning.h", "r+")
print "Name of the file: ", fo.name
line = fo.readlines()
for idx, item in enumerate(line):
    if 'BUILD_INCREMENT' in item:
        tmp_str =  item.split();
        tmp_str[2] = str(int(tmp_str[2]) + 1) + "\n";
        item = ' '.join(tmp_str);
        line[idx] = item;
        break;
fo.seek(0)

for idx, item in enumerate(line):
    fo.write(item)
fo.truncate()

# Close opend file
fo.close()
