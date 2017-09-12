import java.io.BufferedReader;
import java.io.FileReader;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class FileParser
{
    /**
    * This method searches the file FILE_PATH looking for a single C-style define of SYMBOL.
    * If found, the defined SYMBOL's value is assigned using %set command to PROP_NAME Value
    * The parameters are encoded in a string with the format:
    * @param param: FILE_PATH>>>PROP_NAME>>>SYMBOL
    */
    public static String[][] parseCDefine(Object component, String param)
    {
        String output = null;
        String[] params = param.split(">>>");
        if (params.length == 3)
        {
            output = "%set " + params[1] + " Value " + doParseDefine(params[0], params[2]);
        }
        return new String[][] {{}, {output}};
    }

    /**
    * This method searches the file FILE_PATH looking for a list C-style defines of SYMBOL1, SYMBOL2, ..., SYMBOLn
    * If found, the defined SYMBOLs' values are concatenated using DELIM and assigned using %set command to PROP_NAME Value
    * The parameters are encoded in a string with the format:
    * @param param: FILE_PATH>>>PROP_NAME>>>DELIM>>>SYMBOL1>>>SYMBOL2...>>>SYMBOLn
    */
    public static String[][] parseCDefines(Object component, String param)
    {
        String output = null;
        String[] params = param.split(">>>");
        if (params.length >= 4)
        {
            String value = doParseDefine(params[0], params[3]);
            for (int i = 4; i < params.length; i++)
            {
                value += params[2] + doParseDefine(params[0], params[i]);
            }
            output = "%set " + params[1] + " Value " + value;
        }
        return new String[][] {{}, {output}};
    }

    public static String doParseDefine(String filePath, String symbol)
    {
        return doParseRegExp(filePath, "#define\\s+" + symbol + "\\s+([^\\s]+)");
    }

    public static String doParseRegExp(String filePath, String patternString)
    {
        try (BufferedReader br = new BufferedReader(new FileReader(filePath)))
        {
            Pattern pattern = Pattern.compile(patternString);
            String line = null;
            while ((line = br.readLine()) != null)
            {
                Matcher matcher = pattern.matcher(line);
                if (matcher.find())
                {
                    return matcher.group(1);
                }
            }
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
        return null;
    }
}
