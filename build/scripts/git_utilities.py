import os
from typing import Any

from git import Repo
from scripts.utilities import assert_step, use_directory, run


class GitUtilities:
    @staticmethod
    def check_no_uncommitted_changes(repo: Repo) -> None:
        assert_step(not repo.bare)

        # From https://stackoverflow.com/questions/31959425/how-to-get-staged-files-using-gitpython
        repo_location = repo.working_dir
        repo_name = os.path.basename(repo_location)
        assert_step(len(repo.index.diff(None)) == 0, f"there are un-committed changes to {repo_name}")  # Modified
        assert_step(len(repo.index.diff("HEAD")) == 0, f"there are staged changes to {repo_name}")  # Staged

    @staticmethod
    def reset_and_clean_working_directory(project_dir: str) -> None:
        with use_directory(project_dir):
            # Delete untracked files:
            # - does not delete ignored files
            # - does not delete untracked files in new, untracked directories
            run(["git", "clean", "-f"])

            run(["git", "reset", "--hard"])
