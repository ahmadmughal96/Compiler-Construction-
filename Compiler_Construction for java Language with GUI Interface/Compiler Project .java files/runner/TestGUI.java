package runner;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextArea;

import ast.Program;
import ast.VarDecl;
import lexer.Lexer;
import lexer.Token;
import lexer.TokenType;
import parser.Parser;
import semantic.SemanticAnalyzer;
import visitor.PrintVisitor;

@SuppressWarnings("serial")
public class TestGUI extends JPanel {
	private JFrame frame;

	private JPanel codePanel;
	private JPanel buttonPanel;

	private JTabbedPane tabbedPane;

	private JTextArea codeArea;
	private JTextArea lexArea;
	private JTextArea syntaxArea;
	private JTextArea semArea;
	

	private JButton openBtn;
	private JButton runBtn;

	private String sourceCode;
	private File file;
	private FileReader reader;
	private Token token;
	private Program program;
	private PrintVisitor printer;

	public TestGUI(JFrame frame) {
		this.frame = frame;
		this.setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
		codePanel = new JPanel();
		codePanel.setLayout(new BoxLayout(codePanel, BoxLayout.Y_AXIS));
		codeArea = new JTextArea(30, 50);
		codeArea.setBorder(BorderFactory.createLineBorder(Color.black));
		JScrollPane codeScrollPane = new JScrollPane(codeArea);
		codeScrollPane.setAutoscrolls(true);
		codePanel.add(codeScrollPane);

		buttonPanel = new JPanel();
		buttonPanel.setBorder(BorderFactory.createLineBorder(Color.black));

		openBtn = new JButton("Open");
		openBtn.addActionListener(new OpenActionListener());
		buttonPanel.add(openBtn);

		runBtn = new JButton("Run");
		runBtn.addActionListener(new RunActionListener());
		buttonPanel.add(runBtn);

		codePanel.add(buttonPanel);
		this.add(codePanel);

		tabbedPane = new JTabbedPane();

		lexArea = new JTextArea(32, 40);
		lexArea.setEditable(false);
		JScrollPane lexScrollPane = new JScrollPane(lexArea);
		lexScrollPane.setAutoscrolls(true);
		tabbedPane.add("Lexical analysis", lexScrollPane);

		syntaxArea = new JTextArea(32, 40);
		syntaxArea.setEditable(false);
		JScrollPane syntaxScrollPane = new JScrollPane(syntaxArea);
		syntaxScrollPane.setAutoscrolls(true);
		tabbedPane.add("Syntax analysis", syntaxScrollPane);
		
		semArea = new JTextArea(32, 40);
		semArea.setEditable(false);
		JScrollPane semScrollPane = new JScrollPane(semArea);
		semScrollPane.setAutoscrolls(true);
		tabbedPane.add("Semantic analysis", semScrollPane);

		this.add(tabbedPane);

	}

	private String readCodeToString(String filePath) throws IOException {
		StringBuffer fileData = new StringBuffer();
		BufferedReader reader = new BufferedReader(new FileReader(filePath));
		char[] buf = new char[1024];
		int numRead = 0;
		while ((numRead = reader.read(buf)) != -1) {
			String readData = String.valueOf(buf, 0, numRead);
			fileData.append(readData);
			buf = new char[1024];
		}
		reader.close();
		return fileData.toString();
	}

	private class OpenActionListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			JavaFilter javaFilter = new JavaFilter();

			JFileChooser fileChooser = new JFileChooser(new File(System.getProperty("user.dir")
					+ "/resources"));			
			fileChooser.setFileFilter(javaFilter);
			fileChooser.setAcceptAllFileFilterUsed(false);
			int returnValue = fileChooser.showOpenDialog(TestGUI.this);
			if (returnValue == JFileChooser.APPROVE_OPTION) {
				if (javaFilter.getExtension(fileChooser.getSelectedFile()).equals("java")) {
					try {
						file = fileChooser.getSelectedFile();
						reader = new FileReader(file);
						sourceCode = readCodeToString(fileChooser.getSelectedFile().getPath());
						sourceCode += "\n";
						codeArea.setText(sourceCode);
					} catch (IOException e1) {

					}

				}
			}
		}
	}

	private class RunActionListener implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
			lexArea.setText("");
			syntaxArea.setText("");
			semArea.setText("");

			/****************Lexical Analysis************************/
			Lexer lexer = null;
			try {
				lexer = new Lexer(reader);
				do {
					token = lexer.getToken();
					if(token.getType() == TokenType.UNKNOWN){
						// print token type and location
						lexArea.append("   " + token.getType());
						lexArea.append("   " +" (" + token.getLineNumber() + "," + token.getColumnNumber() + ")");
						lexArea.append("\n");
						continue;
					}
					lexArea.append("   " + token.getType());
					lexArea.append("   " + " (" + token.getLineNumber() + "," + token.getColumnNumber() + ")");
						
					// print out values for ID and INT_CONST tokens
					if (token.getType() == TokenType.ID)
						lexArea.append("   " + ": " + token.getAttribute().getIdVal() + "\n");
					else if (token.getType() == TokenType.INT_CONST)
						lexArea.append("   " + ": " + token.getAttribute().getIntVal() + "\n");
					else if (token.getType() == TokenType.FLOAT_CONST)
						lexArea.append("   " + ": " + token.getAttribute().getFloatVal() + "\n");
					else if (token.getType() == TokenType.CHAR_CONST)
						lexArea.append("   " + ": " + token.getAttribute().getCharVal() + "\n");
					else if (token.getType() == TokenType.BOOLEAN_CONST)
						lexArea.append("   " + ": " + token.getAttribute().getBooleanVal() + "\n");
					else
						lexArea.append("\n");
				
				} while (token.getType() != TokenType.EOF);

			} catch (FileNotFoundException e2) {
				// TODO Auto-generated catch block
				e2.printStackTrace();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}					
			finally {
				JOptionPane.showMessageDialog(frame, "Lexical Analysis is completed",
						"Information", JOptionPane.INFORMATION_MESSAGE);
			}
			
			
			/****************Syntax Analysis************************/			
			try {
				reader = new FileReader(file);
				Parser parser = new Parser(reader);
				program = parser.parseProgram();
				for (String r : parser.getErrorList()) {
					syntaxArea.append(r);
				}
				// print out statistics
				syntaxArea.append(parser.getErrors() + " errors reported" + "\n");
				// print out ASTs
				printer = new PrintVisitor();
				printer.visit(program);
				for (VarDecl r : printer.getTreeList()) {
					syntaxArea.append(r + "\n");
				}

			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			finally {
				JOptionPane.showMessageDialog(frame, "Syntax is completed!", "Information",
						JOptionPane.INFORMATION_MESSAGE);
			}
			
			/****************Semantic Analysis************************/
			try {
				// create semantic analyzer
				reader = new FileReader(file);
				SemanticAnalyzer semantic = new SemanticAnalyzer(reader);
				semantic.analyzeProgram();
				for (String r : semantic.getErrorList()) {
					semArea.append(r + "\n");
				}
				semArea.append(semantic.getErrors() + " errors reported" + "\n");
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			finally {
				JOptionPane.showMessageDialog(frame, "Semantic Analysis is completed!", "Information",
						JOptionPane.INFORMATION_MESSAGE);
			}

			
			
			
		}
	}
}
