import os

from scripts.release_constants import release_constants
from scripts.utilities import write_file, read_file, get_file_name


from typing import Dict, List, Union


class Parts:
    def __init__(self, file:str, include_files: List[str]) -> None:
        self.file = file
        self.include_files = include_files

    def __repr__(self) -> str:
        return f"['file': '{self.file}', 'include_files': {self.include_files}]"


class SingleHeaderFile(object):
    @staticmethod
    def create(directory: str) -> str:
        files = SingleHeaderFile.get_all_files(directory)
        files = SingleHeaderFile.sort_by_dependencies(files)
        output_file = os.path.abspath(release_constants.simulated_single_header_file_path)

        includes = '\n'.join(map(lambda f: f'#include "{f}"', files))
        output = ('#ifndef APPROVALTESTS_CPP_APPROVALS_HPP\n'
                  '#define APPROVALTESTS_CPP_APPROVALS_HPP\n'
                  '\n'
                  '// This file is machine-generated. Do not edit.\n'
                  '\n'
                  f'{includes}\n'
                  '\n'
                  '#endif // APPROVALTESTS_CPP_APPROVALS_HPP\n'
                  )
        write_file(output_file, output)
        return output_file

    @staticmethod
    def get_all_files(directory: str) -> List[str]:
        all_files = []
        abs = os.path.abspath(directory)
        relative = get_file_name(abs)

        for root, directories, files in os.walk(directory):
            for file in files:
                if file.endswith('.h'):
                    file_text = os.path.join(root, file)
                    file_text = file_text.replace('./', relative + '/')
                    all_files.append(file_text)
        all_files.sort()
        return all_files

    @staticmethod
    def sort_by_dependencies(files: List[str]) -> List[str]:
        parts = list(map(SingleHeaderFile.get_parts, files))
        return list(map(lambda p: p.file, SingleHeaderFile.sort_parts_by_dependencies(parts)))

    @staticmethod
    def get_parts(file: str) -> Parts:
        # This is effectively creating a Directed Acyclic Graph of all files
        # and their #includes, which we later sort by dependency order.
        content = read_file(os.path.join('..', file))
        lines = content.splitlines()
        include_lines = filter(lambda t: t.startswith('#include "'), lines)
        include_files = list(map(lambda i: i.replace('#include ', '').replace('"', ''), include_lines))
        include_files = list(map(lambda f: get_file_name(f), include_files))
        return Parts(file, include_files)

    @staticmethod
    def sort_parts_by_dependencies(parts: List[Parts]) -> List[Parts]:
        length = len(parts)
        for lower_index in range(length):
            lower = parts[lower_index]
            for higher_index in range(lower_index + 1, length):
                higher = parts[higher_index]
                if SingleHeaderFile.depends_on(lower, higher):
                    parts.remove(higher)
                    parts.insert(0, higher)
                    return SingleHeaderFile.sort_parts_by_dependencies(parts)
        return parts

    @staticmethod
    def depends_on(file1: Parts, file2: Parts) -> bool:
        file2_name = get_file_name(file2.file)
        return file2_name in file1.include_files
