import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;
import javax.swing.JOptionPane;

import java.awt.Color;
import javax.swing.SwingConstants;
import java.awt.Font;
import javax.swing.JButton;
import javax.swing.JTextField;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class BinToDec extends JFrame{

	private JPanel contentPane;
	private JTextField textField_1;
	private JTextField textField_4;

	//----------------------------------------------------------------------
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					myGUI frame = new myGUI();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
//-------------------------------------------------------------------
	public BinToDec() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);

		JLabel lblNewLabel = new JLabel("Welcome to the best Calculator!");
		lblNewLabel.setFont(new Font("Tahoma", Font.BOLD, 14));
		lblNewLabel.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel.setForeground(Color.RED);
		lblNewLabel.setBounds(86, 11, 263, 34);
		contentPane.add(lblNewLabel);

		JLabel lblNewLabel_1 = new JLabel("Enter binary number");
		lblNewLabel_1.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblNewLabel_1.setBounds(50, 53, 173, 20);
		contentPane.add(lblNewLabel_1);

		JLabel lblNewLabel_2 = new JLabel("Decimal answer");
		lblNewLabel_2.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblNewLabel_2.setBounds(50, 135, 173, 20);
		contentPane.add(lblNewLabel_2);


		textField_1 = new JTextField(); //decimal answer
		textField_1.setHorizontalAlignment(SwingConstants.CENTER);
		textField_1.setText("");
		textField_1.setBounds(256, 135, 130, 20);
		contentPane.add(textField_1);
		textField_1.setColumns(10);


		textField_4  = new JTextField(); //binary input
		textField_4.setHorizontalAlignment(SwingConstants.CENTER);
		textField_4.setText("");
		textField_4.setBounds(256, 53, 130, 20);
		contentPane.add(textField_4);
		textField_4.setColumns(10);

		//-------------------------------------------------CALCLATION
		JButton calculate = new JButton("Calculate");

		calculate.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {

				String binaryInput = textField_4.getText();
								
				if(checkBin(binaryInput)==false)
				{
					JOptionPane.showMessageDialog(null, "Only 0 and 1 are allowed!");
					BinToDec newFrame = new BinToDec();
					newFrame.show();
					dispose();
				}
				else
				{
				Integer answer = cal(binaryInput);
				String ans = answer.toString();
				textField_1.setText(ans);
				}

			}
		});

		calculate.setFont(new Font("Tahoma", Font.BOLD, 12));
		calculate.setForeground(new Color(0,0,128));
		calculate.setBounds(62, 190, 95, 40);
		contentPane.add(calculate);
		//------------------------------------------------

		JButton return1 = new JButton("Return");

		return1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				myGUI gui = new myGUI();
				gui.show();
				dispose();
			}
		});

		return1.setFont(new Font("Tahoma", Font.BOLD, 12));
		return1.setForeground(new Color(0,0,128));
		return1.setBounds(286, 190, 95, 40);
		contentPane.add(return1);
	}
//-------------------------------------------------------
	public static int cal(String binaryInput) {
		int answer=0;

		for (int i=0;i<binaryInput.length();i++)
		{
			int power = binaryInput.length()-1-i;
			int digit = Integer.parseInt(String.valueOf(binaryInput.charAt(i)));
			int temp = (int)Math.pow(2, power);
			answer = answer + (digit*temp);				
		}
		return answer;
	}
	//-----------------------------------------------------------
	public static boolean checkBin (String num) {
		for (int i =0; i<num.length(); i++)
		{
			if ((num.charAt(i) != '0') && (num.charAt(i)!='1'))
				return false;
		}
		return true;
	}
}
