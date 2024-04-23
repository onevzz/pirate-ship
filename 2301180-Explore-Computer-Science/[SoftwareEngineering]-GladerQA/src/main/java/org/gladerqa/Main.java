package org.gladerqa;

import java.time.Duration;
import org.openqa.selenium.By;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.edge.EdgeDriver;
import org.openqa.selenium.edge.EdgeOptions;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws Exception {
        // Set options to run on a specific profile to avoid having to sign in manually (Google)
        EdgeOptions options = new EdgeOptions();
        options.addArguments("user-data-dir=C:\\Users\\username\\AppData\\Local\\Microsoft\\Edge\\User Data");
        options.addArguments("profile-directory=Default");
        options.setBinary("C:\\Program Files (x86)\\Microsoft\\Edge\\Application\\msedge.exe");

        // Establish the WebDriver (Microsoft Edge)
        EdgeDriver driver = new EdgeDriver(options);

        // Establish the Element IDs
        String url = "https://example.com";
        String name = "my-name";
        String studentID = "my-id";
        String classButton = "my-2301260";
        String workPrefix = "my-work-"; int workLoad = 20;
        String editor = "my-editor";
        String workAnswerPostfix = "-answer";
        String workAnswerDirectory = "./";
        String submitButton = "my-submit";
        String score = "my-score";

        try {
            // Open up Glader
            driver.get(url);
            // Establish Waiting Strategies
            driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(2));

            // Attempt to Get Full Name
            WebElement nameBox = driver.findElement(By.id(name));
            System.out.println("Full Name: " + nameBox.getText());

            // Attempt to Get Student ID
            WebElement studentIDBox = driver.findElement(By.id(studentID));
            System.out.println("Student ID: " + studentIDBox.getText());

            // Enter the Specified Class
            WebElement classButtonBox = driver.findElement(By.id(classButton));
            classButtonBox.click();
            System.out.println("Entered Class (ID): " + classButton);

            // Save the Class URL to return to after each work is submitted
            String targetClass = driver.getCurrentUrl();

            // Loop i times, when i represents the amount of assignments in that class
            for (int i = 1; i <= workLoad; i++) {
                // Assemble together each assignment element id, and click it (ready, set, go!)
                String workFull = workPrefix + i;
                WebElement workButtonBox = driver.findElement(By.id(workFull));
                workButtonBox.click();
                //System.out.println("Entered Work Editor (ID): " + workFull);

                // Clear and Fill in the Answer located in the specified file into the editor
                WebElement editorBox = driver.findElement(By.id(editor));
                editorBox.clear();
                try {
                    File answerFile = new File(workAnswerDirectory + workFull + workAnswerPostfix);
                    Scanner brother = new Scanner(answerFile);
                    while (brother.hasNextLine()) {
                        String data = brother.nextLine();
                        editorBox.sendKeys(data);
                    }
                    brother.close();
                } catch (FileNotFoundException err) {
                    System.out.println("An Error Occurred While Reading the Answer Files!");
                    err.printStackTrace();
                }

                // Submit the Assignment
                WebElement submitButtonBox = driver.findElement(By.id(submitButton));
                submitButtonBox.click();
                //System.out.println("Submitted Work (ID): " + submitButton);

                // Attempt to Get Score
                WebElement scoreBox = driver.findElement(By.id(score));
                System.out.printf("Score (%d): %s%n", i, scoreBox.getText());

                // Return to the Class URL
                driver.get(targetClass);
            }

            // Test Completed, Print the results!
            System.out.println("----------------------------------------");
            System.out.println("Test Completed @ Class (ID): " + classButton);

            Thread.sleep(5000);
        } finally {
            driver.quit();
        }
    }
}