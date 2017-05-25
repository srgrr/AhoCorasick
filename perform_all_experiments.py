'''
    This script builds and runs all the experiments
    (see Makefile)
'''
import subprocess
import time
import glob
import sys
import os

subprocess.call(['make', 'clean'])
subprocess.call(['make', 'main'])
subprocess.call(['rm', 'data', '-rf'])
subprocess.call(['rm', 'results', '-rf'])

algorithms = ['aho', 'kmp', 'bfa']

def create_dir(dirname):
    try:
        os.makedirs(dirname)
        print 'Created directory %s'%dirname
    except:
        pass

def run_experiment(pattern_file, text_file, output_folder):
    print 'Running experiment (%s, %s)'%(pattern_file, text_file)
    text_file_name = os.path.split(text_file)[-1]
    pattern_file_name = os.path.split(pattern_file)[-1]
    outputs = []
    for algo in algorithms:
        start_time = time.time()
        outputs.append(subprocess.check_output(['./bin/main', pattern_file, text_file, algo]))
        print '%s -> %.08fs'%(algo, time.time()- start_time)

    if any([x != outputs[0] for x in outputs]):
        print 'ERROR at %s %s'%(pattern_file, text_file)
        for (outp1, alg1) in zip(outputs, algorithms):
            for (outp2, alg2) in zip(outputs, algorithms):
                if alg1 > alg2: continue
                if outp1 != outp2:
                    print 'ALGORITHMS %s AND %s MISMATCH'%(alg1, alg2)
        for (output, algo) in zip(outputs, algorithms):
            open(os.path.join(output_folder, '%s-%s.%s'%(pattern_file_name, text_file_name, algo)), 'w').write(output)
        sys.exit(1)
    print '(Outputs match)'
    for (output, algo) in zip(outputs, algorithms):
        open(os.path.join(output_folder, '%s-%s.%s'%(pattern_file_name, text_file_name, algo)), 'w').write(output)

subprocess.call(['python', 'download_data.py'])
create_dir('results')

'''
    Create synthetic datasets
'''
create_dir('results/synthetic')
# AHO vs KMP vs BFA on single-pattern matching
pattern = 'a'*19999 + 'b'
text = 'a'*1000000
create_dir('data/patterns/synthetic')
create_dir('data/synthetic')
open('data/patterns/synthetic/1.txt', 'w').write(pattern)
open('data/synthetic/1.txt', 'w').write(text)

run_experiment('data/patterns/synthetic/1.txt', 'data/synthetic/1.txt', 'results/synthetic')


'''
    Perform bibliographic experiments
'''
patterns = 'data/patterns/english_words.txt'
books_folder = 'data/books'

result_category = 'results/books'

create_dir('results/books')

content = open(patterns).readlines()[:1000]
open(patterns, 'w').write(''.join(content))

for book in glob.iglob('data/books/*'):
    run_experiment(patterns, book, 'results/books')
