import sqlite3

PATH = "kashthealien@gmail.com-GoogleMail#database.db"
user = "yogeshwar1989@gmail.com"
LINE_BREAK = "\n________________________________________________________________\n"
emots = [":)", ":p", ":d", ":(", ":'(", "lol",".."]
evals = [1, 4, 3, -2, -7, 10, 0]
LIMIT = u'Chat with ' + user
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
	count = 1
	while 1:
		try:
			st = "Chat: "+str(count) +"\n"
			mymessage = messages.next()
			if not unicode(mymessage[3]) == LIMIT :continue
			message = fixMessage(clean(unicode(mymessage[1])))
			st += message
			st += LINE_BREAK
			sentimentValue = 0
			counts = []
			vals = []
			for i in range(len(emots)):
				counts.append(0)
				vals.append(0)
			for i in range(len(emots)):
				counts[i] += message.lower().count(emots[i])
				vals[i] = evals[i]*counts[i]
				sentimentValue += vals[i]
				st += emots[i].upper() + " = " + str(counts[i]) + " | "
			st += "\n\n*SentimentValue* = " +str(sentimentValue) + "  || *Length* = " + str(len(message))
			st += LINE_BREAK
			sentiments.append(sentimentValue)
			lengths.append(len(message))
			print st.encode('ascii', 'ignore')
			count += 1
		except Exception as inst:
			#print type(inst)
			#print inst.args
			break

for i in range(len(sentiments)):
	print sentiments[i], lengths[i]
