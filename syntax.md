## Minishell syntax

\<syntax> ::= \<line> | \<line> "|" \<syntax>
<br /><br />

\<line>   ::= \<opt-whitespaces> \<cmd> \<opt-whitespaces> |
\<opt-whitespaces> "<" \<opt-whitespaces>  \<file-name> \<line>
|
\<line> ">" \<opt-whitespaces> \<file-name> \<opt-whitespaces>
<br /><br />

\<opt-whitespaces> ::= " "  |  " "  \<opt-whitespaces>
<br /><br />

