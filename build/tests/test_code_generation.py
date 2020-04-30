import unittest
import pyperclip

from approvaltests.approvals import verify
from scripts.multiline_string_utilities import remove_indentation
from tests.helpers import diff_merge_reporter
# Convenience variable, so we can paste in code and run test_demo_convert_to_concatenation.
# This is at global scope to prevent PyCharm reformatting the indentation when we
# paste code in.

to_concatenated_string = 'your string here'

to_multiline_string = ('your string here')

class CodeGeneration:
    @staticmethod
    def convert_concatenation_to_multiline(content: str) -> str:
        lines = content.splitlines()
        code = "remove_indentation << f'''\n"
        for line in lines:
            code += line + '\n'
        code += "'''"
        return code

    @staticmethod
    def convert_string_to_concatenation(content: str) -> str:
        lines = content.splitlines()
        code = '('
        for line in lines:
            if '{' in line:
                code += 'f'
            code += f"'{line}\\n'\n"
        code += ')'
        return code

    @staticmethod
    def convert_string_to_joined_list(content: str) -> str:
        lines = content.splitlines()
        code = "'\\n'.join([\n"
        for line in lines:
            if '{' in line:
                code += 'f'
            code += f"'{line}',\n"
        code += '])'
        return code


class TestCodeGeneration(unittest.TestCase):
    def test_convert_string_to_concatentation(self) -> None:
        content = remove_indentation << '''
        
            toc
            
            ## v.x.y.z
            
            {self.old_feature_text()}
            
            '''
        result = CodeGeneration.convert_string_to_concatenation(content)
        expected = remove_indentation << r"""
            ('\n'
            'toc\n'
            '\n'
            '## v.x.y.z\n'
            '\n'
            f'{self.old_feature_text()}\n'
            '\n'
            )"""
        self.assertEqual(expected, result)

    def test_convert_string_to_joined_list(self) -> None:
        content = remove_indentation << '''
        
            toc
            
            ## v.x.y.z
            
            {self.old_feature_text()}
            
            '''
        result = CodeGeneration.convert_string_to_joined_list(content)
        expected = remove_indentation << r"""
            '\n'.join([
            '',
            'toc',
            '',
            '## v.x.y.z',
            '',
            f'{self.old_feature_text()}',
            '',
            ])"""
        self.assertEqual(expected, result)

    def test_concatentation_to_multiline(self) -> None:

        input = ('\n'
            'toc\n'
            '\n'
            '## v.x.y.z\n'
            '\n'  
            '{self.old_feature_text()}\n'
            '\n'
            )
        output = CodeGeneration.convert_concatenation_to_multiline(input)
        verify(output, diff_merge_reporter)

    def test_entry_point_for_convert_to_concatenation(self) -> None:
        if to_concatenated_string != 'your string here':
            pyperclip.copy(CodeGeneration.convert_string_to_concatenation(to_concatenated_string))
            print("converted concatened text copied to clipboard")

    def test_entry_point_for_convert_to_multiline(self) -> None:
        if to_multiline_string != 'your string here':
            code = CodeGeneration.convert_concatenation_to_multiline(to_multiline_string)
            print(code)
            pyperclip.copy(code)
            print("converted multiline text copied to clipboard")


if __name__ == '__main__':
    unittest.main()
