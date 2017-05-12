

#define UART_TX_BUF_SIZE                256                                         /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE                256                                         /**< UART RX buffer size. */


void uart_init(void);
void uart_send(char *SenStr ,unsigned short int SenLen);
