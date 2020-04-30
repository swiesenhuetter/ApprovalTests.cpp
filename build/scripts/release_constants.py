import os


class ReleaseConstants:
    def __init__(self) -> None:

        self.approval_tests_dir = F"../ApprovalTests"
        self.build_dir = F"../build"
        self.release_dir = F"../build/releases"

        self.main_project_dir = F"../../ApprovalTests.Cpp"
        self.starter_project_dir = F"../../ApprovalTests.Cpp.StarterProject"

        self.simulated_single_header_file_path = os.path.join(self.approval_tests_dir, "ApprovalTests.hpp")

        self.xxx_release_notes_path = os.path.join(self.build_dir, F'relnotes_x.y.z.md')
        self.release_notes_dir = os.path.join(self.build_dir, 'release_notes')
        self.template_release_notes_path = os.path.join(self.release_notes_dir, F'relnotes_template.md')


release_constants = ReleaseConstants()
