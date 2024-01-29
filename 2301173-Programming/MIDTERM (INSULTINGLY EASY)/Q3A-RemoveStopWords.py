def remove_stop_words(message):
    STOP_WORDS = ['to','is','am','are','a','the','of','in','with','on','under'] # Do not alter
    hell = []
    for i in message.strip().split():
        if not i in STOP_WORDS:
            hell.append(i)
    return hell

def count(word_list):
    hell = dict()
    for i in word_list:
        if not i in hell:
            hell.update( { i : 1 } )
        else:
            hell.update( { i : hell[i]+1 } )
    return hell