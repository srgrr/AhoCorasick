'''
    This script builds and runs all the experiments
    (see Makefile)
'''
import subprocess
import pylab as plt
import time
import glob
import sys
import os

alphabet = "abcdefghijklmnopqrstuvwxyz"

subprocess.call(['make', 'clean'])
subprocess.call(['make', 'main'])
subprocess.call(['rm', 'data', '-rf'])
subprocess.call(['rm', 'patterns', '-rf'])
subprocess.call(['rm', 'results', '-rf'])

algorithms = ['aho', 'kmp', 'bfa', 'trie']

def create_dir(dirname):
    try:
        os.makedirs(dirname)
        print('Created directory %s'%dirname)
    except:
        pass

def run_experiment(pattern_file, text_file, output_folder):
    print('Running experiment (%s, %s)'%(pattern_file, text_file))
    text_file_name = os.path.split(text_file)[-1]
    pattern_file_name = os.path.split(pattern_file)[-1]
    outputs = []
    ellapsed = []
    for algo in algorithms:
        start_time = time.time()
        outputs.append(subprocess.check_output(['./bin/main', pattern_file, text_file, algo]))
        print('%s -> %.08fs'%(algo, time.time()- start_time))
        ellapsed.append(time.time() - start_time)
    if any([x != outputs[0] for x in outputs]):
        print('ERROR at %s %s'%(pattern_file, text_file))
        for (outp1, alg1) in zip(outputs, algorithms):
            for (outp2, alg2) in zip(outputs, algorithms):
                if alg1 > alg2: continue
                if outp1 != outp2:
                    print('ALGORITHMS %s AND %s MISMATCH'%(alg1, alg2))
        for (output, algo) in zip(ellapsed, algorithms):
            open(os.path.join(output_folder, '%s-%s.%s'%(pattern_file_name, text_file_name, algo)), 'w').write(str(output))
        sys.exit(1)
    print('(Outputs match)')
    for (output, algo) in zip(ellapsed, algorithms):
        open(os.path.join(output_folder, '%s-%s.%s'%(pattern_file_name, text_file_name, algo)), 'w').write(str(output))
    return ellapsed

subprocess.call(['python', 'download_data.py'])
create_dir('results')

'''
    Create synthetic datasets
'''
create_dir('results/synthetic/big')
# AHO vs KMP vs BFA on single-pattern matching
pattern = 'a'*1999 + 'b'
text = 'a'*100000
create_dir('patterns/synthetic/big')
create_dir('data/synthetic/big')
open('patterns/synthetic/big/1.txt', 'w').write(pattern)
open('data/synthetic/big/1.txt', 'w').write(text)

run_experiment('patterns/synthetic/big/1.txt', 'data/synthetic/big/1.txt', 'results/synthetic/big')

'''
    Create progressive datasets
'''
create_dir('patterns/synthetic/progressive')
create_dir('data/synthetic/progressive')
create_dir('results/synthetic/progressive')

# progressive wrt text length
#lengths = range(1000000, 101000000, 1000000)
lengths = range(1000, 10001, 1000)
times = []
for i in range(len(algorithms)):
    times.append([])
for i in lengths:
    pattern = 'aaaaaaaaaaaaaaab'
    open('patterns/synthetic/progressive/text_length.txt', 'w').write(pattern)
    text = 'a'*i
    open('data/synthetic/progressive/text_length_%d.txt'%i, 'w').write(text)
    obtained_times = run_experiment('patterns/synthetic/progressive/text_length.txt', 'data/synthetic/progressive/text_length_%d.txt'%i, 'results/synthetic/progressive')
    for i in range(len(algorithms)):
        times[i].append(obtained_times[i])

plt.figure('vs'.join(algo for algo in algorithms))
plt.xlabel('Text length')
plt.ylabel('Time (seconds)')

plots = []

for i in range(len(algorithms)):
    plots.append(plt.plot(lengths, times[i], label=algorithms[i])[0])

plt.legend(handles=plots)

plt.savefig('results/synthetic/progressive/text_length.png')
plt.close()

# progressive wrt pattern count
lengths = range(1, 101)
times = []
for i in range(len(algorithms)):
    times.append([])
for i in lengths:
    pattern = 'aaaaaaaaaaaaaaab\n'*i
    open('patterns/synthetic/progressive/pattern_count_%d.txt'%i, 'w').write(pattern)
    text = 'a'*1000000
    open('data/synthetic/progressive/pattern_count.txt', 'w').write(text)
    obtained_times = run_experiment('patterns/synthetic/progressive/pattern_count_%d.txt'%i, 'data/synthetic/progressive/pattern_count.txt', 'results/synthetic/progressive')
    for i in range(len(algorithms)):
        times[i].append(obtained_times[i])

plt.figure('vs'.join(algo for algo in algorithms))
plt.xlabel('Pattern count')
plt.ylabel('Time (seconds)')

plots = []

for i in range(len(algorithms)):
    plots.append(plt.plot(lengths, times[i], label=algorithms[i])[0])

plt.legend(handles=plots)

plt.savefig('results/synthetic/progressive/pattern_count.png')
plt.close()

# progressive wrt pattern length
lengths = range(100, 1100, 100)
times = []
for i in range(len(algorithms)):
    times.append([])
for i in lengths:
    pattern = 'a'*(i-1) + 'b'
    open('patterns/synthetic/progressive/pattern_length_%d.txt'%i, 'w').write(pattern)
    text = 'a'*1000000
    open('data/synthetic/progressive/pattern_length.txt', 'w').write(text)
    obtained_times = run_experiment('patterns/synthetic/progressive/pattern_length_%d.txt'%i, 'data/synthetic/progressive/pattern_length.txt', 'results/synthetic/progressive')
    for i in range(len(algorithms)):
        times[i].append(obtained_times[i])

plt.figure('vs'.join(algo for algo in algorithms))
plt.xlabel('Pattern length')
plt.ylabel('Time (seconds)')

plots = []

for i in range(len(algorithms)):
    plots.append(plt.plot(lengths, times[i], label=algorithms[i])[0])

plt.legend(handles=plots)

plt.savefig('results/synthetic/progressive/pattern_length.png')
plt.close()

'''
    Perform bibliographic experiments
'''
patterns = 'patterns/english_words.txt'
books_folder = 'data/books'

result_category = 'results/books'

create_dir('results/books')

content = open(patterns).readlines()[:1000]
open(patterns, 'w').write(''.join(content))

for book in glob.iglob('data/books/*'):
    run_experiment(patterns, book, 'results/books')
