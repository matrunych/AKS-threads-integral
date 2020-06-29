from subprocess import Popen, PIPE
import sys

def run_program(num_of_run, config_file):
    res_lst = []
    time = []

    for _ in range(int(num_of_run)):
        cpp_prog = Popen('build/threads_integration {}'.format(config_file), shell=True, stdout=PIPE, stdin=PIPE)
        result = cpp_prog.stdout.readlines()
        res_lst.append(float(str(result[0]).split()[1][:-3]))
        time.append(float(str(result[3]).split()[1][:-3]))


    minimal = min(time)
    print ("Minimal time: ", minimal)



    for i in range(len(res_lst) - 1):
        if res_lst[i] == res_lst[i+1]:
            return "Same result"
        return "Not same"




if __name__ == "__main__":
    print(run_program(sys.argv[1], sys.argv[2]))
