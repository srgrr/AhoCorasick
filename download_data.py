'''
    This script will check that we have all of our datasets available
    and download the ones that are not there.
'''
import os
import wget
to_download = [
'https://ocw.mit.edu/ans7870/6/6.006/s08/lecturenotes/files/t8.shakespeare.txt',
'https://raw.githubusercontent.com/first20hours/google-10000-english/master/google-10000-english-no-swears.txt'
]

names = [
'data/books/shakespeare.txt',
'patterns/english_words.txt'
]

def create_dir(dirname):
    try:
        os.makedirs(dirname)
        print 'Created directory %s'%dirname
    except:
        pass

create_dir('data')
create_dir('data/books')
create_dir('patterns')

for (resource, dest) in zip(to_download, names):
    if True or not os.path.exists(dest):
        print
        print
        print 'Downloading %s...'%os.path.split(dest)[-1]
        wget.download(resource, out=dest)

# set the contents to lowercase

for book in names:
    content = open(book).read().lower()
    open(book, 'w').write(content)

print
print
