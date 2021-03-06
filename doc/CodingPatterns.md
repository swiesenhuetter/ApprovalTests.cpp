<!--
GENERATED FILE - DO NOT EDIT
This file was generated by [MarkdownSnippets](https://github.com/SimonCropp/MarkdownSnippets).
Source File: /doc/mdsource/CodingPatterns.source.md
To change this file edit the source file and then execute ./run_markdown_templates.sh.
-->

<a id="top"></a>

# CodingPatterns

<!-- toc -->
## Contents

  * [Static variables for header-only releases](#static-variables-for-header-only-releases)<!-- endtoc -->

## Static variables for header-only releases

Here is a sample of the pattern that we are using:

<!-- snippet: static_variable_sample -->
<a id='snippet-static_variable_sample'/></a>
```h
private:
    static std::shared_ptr<Reporter>& defaultReporter()
    {
        static std::shared_ptr<Reporter> reporter = std::make_shared<DiffReporter>();
        return reporter;
    }

public:
    static std::shared_ptr<Reporter> getDefaultReporter()
    {
        return defaultReporter();
    }

    static void setDefaultReporter(const std::shared_ptr<Reporter>& reporter)
    {
        defaultReporter() = reporter;
    }
```
<sup><a href='/ApprovalTests/reporters/DefaultReporterFactory.h#L13-L31' title='File snippet `static_variable_sample` was extracted from'>snippet source</a> | <a href='#snippet-static_variable_sample' title='Navigate to start of snippet `static_variable_sample`'>anchor</a></sup>
<!-- endsnippet -->

Note the use of the reference (&) on the return type of the private method, and the addition of a getter and setter method.

---

[Back to User Guide](/doc/README.md#top)
