#include<stdio.h>
#include<stdlib.h>


int checkPresent(int val, int frame[100], int frame_size) {
    int flag = 0;
    for (int j = 0; j < frame_size; j++) {
        if (val == frame[j]) {
            flag = 1;
            break;
        }
    }

    return flag;

}

void setCheck(int checkframe[100], int frame_size) {
    for (int i = 0; i < frame_size; i++) {
        checkframe[i] = -1;
    }
}

void replacePage(int call[100], int size, int frame_size) {
    int frame[frame_size];
    int checkframe[frame_size];
    int count = 0, empty = frame_size, pf = 0;

    for (int i = 0; i < frame_size; i++) {
        frame[i] = -1;
    }

    for (int i = 0; i < size; i++) {

        if (empty > 0) {
            if (checkPresent(call[i], frame, frame_size) == 0) {
                frame[frame_size - empty] = call[i];
                pf++;
                empty--;
            } else 
                continue;
        } else {
            if (checkPresent(call[i], frame, frame_size) == 1) 
                continue;

            int last = 0;
            setCheck(checkframe, frame_size);
            for (int j = 0; j < frame_size; j++) {

                for (int k = i + 1; k < size; k++) {
                    if (call[k] == frame[j]) {
                        last = j;
                        checkframe[j] = j;
                    }
                }

            }
            
            for (int j = frame_size; j >= 0; j--) {
                if (checkframe[j] == -1) {
                    last = j;
                    break;
                }
            }

            frame[last] = call[i];
            pf++;
        }

        printf("\nFrame Status %d : ", count);
        count++;
        for (int m = 0; m < frame_size; m++) {
            if (frame[m] >= 0)
                printf("%d ", frame[m]);
        }
    }

    printf("\nNo. of page faults : %d", pf);
}

int main() {
    int frame_size;
    printf("OPTIMAL PAGE REPLACEMENT\n\n");
    printf("Enter Frame Size :");
    scanf("%d", &frame_size);

    int call[100], size;
    printf("Enter the number of calls to be made : ");
    scanf(" %d", &size);
    printf("Enter array list of pages to be used in order\n");
    for (int i = 0; i < size; i++)
        scanf(" %d", &call[i]);

    replacePage(call, size, frame_size);
    printf("\n");
    
    return 0;
}