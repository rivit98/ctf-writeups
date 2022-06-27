# CursedNova, FAQ, web

## Description
Check out the FAQ!

## Solution

Inspecting the `includes\pages\game\ShowQuestionsPage.class.php` gives us answer immediately:

```
    public function show()
    {
        global $LNG;

        $LNG->includeData(array('FAQ'));
        header("Secret: " . $LNG['W7_FAQ']);
        $this->display('page.questions.default.tpl');
    }
```

Flag will be transmitted in the request headers.

Flag: `CURSEDNOVA{The_answer_you_were_looking_for_Euj4ar8e}`