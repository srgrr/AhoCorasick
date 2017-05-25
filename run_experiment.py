import sys
import time
import subprocess

algorithms = ['aho', 'bf', 'kmp']

def run_experiment(pattern_file, text_file, algorithm):
    start_time = time.time()
    result = subprocess.check_output(['./bin/main', pattern_file, text_file, algorithm])
    print '%s = %.08f s'%(algorithm, time.time() - start_time)
    return result


def main():
    pattern_file, text_file = sys.argv[1:]
    print '---- EXPERIMENT ----'
    print 'PATTERNS: %s'%pattern_file
    print 'TEXT: %s'%text_file
    outputs = [run_experiment(pattern_file, text_file, alg) for alg in algorithms]
    if any([x != outputs[0] for x in outputs[1:]]):
        print 'ERROR, outputs mismatch with dataset [ %s, %s]'%(pattern_file, text_file)
        sys.exit(1)


if __name__ == '__main__':
    main()
