import sqlite3

PATH = "kashthealien@gmail.com-GoogleMail#database.db"
user = "bhavin137@gmail.com"
LINE_BREAK = "\n________________________________________________________________\n"
emots = [":)", ":p", ":d", ":(", ":'(", "lol",".."]
evals = [1, 4, 3, -2, -7, 10, 0]
sentiments = []
lengths = []
# Cleans a text by removing tags
def clean(in_text):
	s_list = list(in_text)
	i,j = 0,0
	while i < len(s_list):
		# iterate until a left-angle bracket is found
		if s_list[i] == '<':
			if s_list[i+1] == 'b' and s_list[i+2] == 'r' and s_list[i+3] == '>':
				i=i+1
				continue				
			while s_list[i] != '>':
				# pop everything from the the left-angle bracket until the right-angle bracket
				s_list.pop(i)
			# pops the right-angle bracket, too
			s_list.pop(i)

		elif s_list[i] == '\n':
			s_list.pop(i)
		else:
			i=i+1
	# convert the list back into text
	join_char=''
	return (join_char.join(s_list)).replace("<br>","\n").replace("&#39;","\'")\
		.replace("&quot;",'"').replace("&quot;",'\"').replace("&gt;",">").replace("&lt;","<")


def fixMessage(text):
	return text.replace(user+":","\n"+user+":").replace("me:","\nme:").replace("PM","\n").replace("AM","\n")
	
# Connect to data base
conn = sqlite3.connect(PATH)
tables = conn.execute('SELECT name FROM sqlite_master WHERE type = "table"')
#for table in tables:
#    print table


# Print all chats
tablesList =['MessagesFT_content']
for tableName in tablesList:
	comm = 'SELECT * FROM ' + tableName
	messages = conn.execute(comm)
	while 1:
		try:
			mymessage = messages.next()
			if not unicode(mymessage[3]) == user : continue
			message = fixMessage(clean(unicode(mymessage[1])))
			print message.encode('ascii', 'ignore')
			print LINE_BREAK
		except Exception as inst:
			print type(inst)
			break

