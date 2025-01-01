import re

logfile = open('.\\log.txt','r')
outpath = 'Analysis_result.txt'
f = open(outpath,'w')
print("open files")

vip_data =[]
member_data = []
count = 0
for line in  logfile:
    line = line.rstrip("\n")
    y = re.findall('(\S+) buys (\S+) for \$(\S+)',line)
    if(re.search('^\[VIP\].*',line)):
        vip_data.append(y[0])
    else:
        member_data.append(y[0])

    count = count +1

#--------資料整理--------------#
vip_dict = {}
member_dict = {}
total_dict={}

for i in range(len(vip_data)):
    if vip_data[i][0] in vip_dict.keys():
        thing_dict = vip_dict.get(vip_data[i][0])
    else:
        thing_dict = {}

    if vip_data[i][1] in thing_dict.keys():
        thing_dict[vip_data[i][1]] = int(thing_dict.get(vip_data[i][1])) +int(vip_data[i][2])
    else:
        thing_dict[vip_data[i][1]] = vip_data[i][2]
    vip_dict[vip_data[i][0]]=thing_dict

for i in range(len(member_data)):
    if member_data[i][0] in member_dict.keys():
        thing_dict = member_dict.get(member_data[i][0])
    else:
        thing_dict = {}
    if member_data[i][1] in thing_dict.keys():
        thing_dict[member_data[i][1]] = int(thing_dict.get(member_data[i][1])) +int(member_data[i][2])
    else:
        thing_dict[member_data[i][1]] = member_data[i][2]

    member_dict[member_data[i][0]] = thing_dict


for i in range(len(vip_data)):
    if vip_data[i][1] in total_dict.keys():
        total_dict[vip_data[i][1]] = int(total_dict.get(vip_data[i][1])) +int(vip_data[i][2])
    else:
        total_dict[vip_data[i][1]] = vip_data[i][2]

for i in range(len(member_data)):
    if member_data[i][1] in total_dict.keys():
        total_dict[member_data[i][1]] = int(total_dict.get(member_data[i][1])) +int(member_data[i][2])
    else:
        total_dict[member_data[i][1]] = member_data[i][2]


#----輸出成TXT---------#
print("[VIP]")
f.write("[VIP]\n")
for key in vip_dict.keys():
    print(f"{key} buys ",end = "")
    save_line = ""
    save_line = f"{key} buys "
    count = 0
    for thing_key in vip_dict.get(key).keys():
        save_line = save_line+"{}:{} ".format(thing_key,vip_dict.get(key).get(thing_key))
        if count == len(vip_dict.get(key))-1:
            save_line = save_line+"\n"
        else:
            save_line = save_line+","
        count = count +1
    print(save_line,end = "")
    f.write(save_line)

print("\n[Member]")
f.write("\n[Member]\n")
for key in member_dict.keys():
    save_line = ""
    save_line = f"{key} buys "
    count = 0
    for thing_key in member_dict.get(key).keys():
        save_line = save_line+"{}:{} ".format(thing_key,member_dict.get(key).get(thing_key))
        if count == len(member_dict.get(key))-1:
            save_line = save_line+"\n"
        else:
            save_line = save_line+","
        count = count +1
    print(save_line,end = "")
    f.write(save_line)

f.write("\n")
print("\n")
for key in total_dict.keys():
    print("Total {} sales: {}".format(key,total_dict.get(key)))
    f.write("Total {} sales: {}".format(key,total_dict.get(key)))
    f.write("\n")

logfile.close()
f.close()
