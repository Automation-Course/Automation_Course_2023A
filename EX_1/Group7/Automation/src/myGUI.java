
import java.awt.BorderLayout;
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

public class myGUI extends JFrame {

	private JPanel contentPane;

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

	public myGUI() {
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

	

		JButton decToBin_Button = new JButton("Decinal To Binary");
		decToBin_Button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				
				DecToBin calculate = new DecToBin();
				calculate.show();
				dispose();
			}
		});

		decToBin_Button.setFont(new Font("Tahoma", Font.BOLD, 12));
		decToBin_Button.setForeground(new Color(0,0,128));
		decToBin_Button.setBounds(50, 80, 150, 100);
		contentPane.add(decToBin_Button);
//------------------------------------------------
		JButton binToDec_Button = new JButton("Binary To Decimal");

		binToDec_Button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				BinToDec calculate = new BinToDec();
				calculate.show();
				dispose();
			}
		});

		binToDec_Button.setFont(new Font("Tahoma", Font.BOLD, 12));
		binToDec_Button.setForeground(new Color(0,0,128));
		binToDec_Button.setBounds(220, 80, 150, 100);
		contentPane.add(binToDec_Button);
//------------------------------------------------------------		
		JButton exitButton = new JButton("EXIT");
		exitButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				JFrame frame=new JFrame("Exit");
				if (JOptionPane.showConfirmDialog(frame, "Are you sure you want to exit?", "Exit",JOptionPane.YES_NO_OPTION)==JOptionPane.YES_NO_OPTION)
					System.exit(0);
			}
		});
		exitButton.setFont(new Font("Tahoma", Font.BOLD, 12));
		exitButton.setForeground(Color.BLACK);
		exitButton.setBounds(300, 220, 89, 23);
		contentPane.add(exitButton);


	}

}
