
import os
import filecmp

NUMBER_OF_TESTS = len(os.listdir('test/snippets'))
FAILED_TESTS = []
    
def serialize_every_snippet():
    for i in range(NUMBER_OF_TESTS): 
        dir = 'test' + str(i + 1)
        os.system(f'./verse -c test/snippets/{dir}/*.verse -o test/snippets/{dir}/out.xml test/snippets/{dir}/out.json')
    
def expect_true(flag):
    if flag: return '\033[92m \t AS EXPECTED \033[0m'
    else: return '\033[91m \t ERROR (MISMATCH) \033[0m'

def compare_serialization_outputs():
    for i in range(NUMBER_OF_TESTS):
        dir = 'test' + str(i+1)
        xml_serialization_outcome = filecmp.cmp(f'test/snippets/{dir}/out.xml',f'test/expected/{dir}/reference.xml')
        json_serialization_outcome = filecmp.cmp(f'test/snippets/{dir}/out.json',f'test/expected/{dir}/reference.json')
        if not xml_serialization_outcome or not json_serialization_outcome: FAILED_TESTS.append(i+1)
        print(f'TEST{i+1} \n \t JSON SERIALIZATION: {expect_true(json_serialization_outcome)} \n\t XML SERIALIZATION: {expect_true(xml_serialization_outcome)} \n')

def show_test_recap():
    for failed_test_id in FAILED_TESTS: print(f'\033[91mTEST no. {failed_test_id} FAILED \033[0m\n')
    print(f'total errors: {len(FAILED_TESTS)}')

if __name__ == "__main__":
    serialize_every_snippet()
    compare_serialization_outputs()
    show_test_recap()