/******************************************************************
 *****                                                        *****
 *****  Name: ethmac.h                                        *****
 *****  Ver.: 1.0                                             *****
 *****  Date: 07/05/2001                                      *****
 *****  last release: 13.4.2018
 *****  Auth: Andreas Dannenberg                              *****
 *****        HTWK Leipzig                                    *****
 *****        university of applied sciences                  *****
 *****        Germany                                         *****
 *****        adannenb@et.htwk-leipzig.de
 *****        V. Pilloux                    *****
 *****  Func: header-file for cs8900.c                        *****
 *****                                                        *****
 ******************************************************************/

// Modifications by Code Red Technologies for NXP LPC1768
// Filename changed to ethmac.h as no longer for cs8900

// CodeRed - update for new header filename

#ifndef __ETHMAC_H
#define __ETHMAC_H

#include <stdbool.h>

#define MYMAC_1              1                   // our ethernet (MAC) address
#define MYMAC_2              2                   // (MUST be unique in LAN!)
#define MYMAC_3              3
#define MYMAC_4              4
#define MYMAC_5              5
#define MYMAC_6              6

#define NUM_FRAG  2			// forced to 2 as double buffering is required in this implementation

typedef struct {
	unsigned char *packet;
	unsigned ctrl;
} desc_t;

typedef struct {
	unsigned info;
	unsigned hash;
} stat_t;

typedef struct {
	desc_t desc[NUM_FRAG];
	stat_t stat[NUM_FRAG];
} eth_t;


/* MAC Configuration Register 1 */
#define MAC1_REC_EN         0x00000001  /* Receive Enable                    */
#define MAC1_PASS_ALL       0x00000002  /* Pass All Receive Frames           */
#define MAC1_RX_FLOWC       0x00000004  /* RX Flow Control                   */
#define MAC1_TX_FLOWC       0x00000008  /* TX Flow Control                   */
#define MAC1_LOOPB          0x00000010  /* Loop Back Mode                    */
#define MAC1_RES_TX         0x00000100  /* Reset TX Logic                    */
#define MAC1_RES_MCS_TX     0x00000200  /* Reset MAC TX Control Sublayer     */
#define MAC1_RES_RX         0x00000400  /* Reset RX Logic                    */
#define MAC1_RES_MCS_RX     0x00000800  /* Reset MAC RX Control Sublayer     */
#define MAC1_SIM_RES        0x00004000  /* Simulation Reset                  */
#define MAC1_SOFT_RES       0x00008000  /* Soft Reset MAC                    */

/* MAC Configuration Register 2 */
#define MAC2_FULL_DUP       0x00000001  /* Full Duplex Mode                  */
#define MAC2_FRM_LEN_CHK    0x00000002  /* Frame Length Checking             */
#define MAC2_HUGE_FRM_EN    0x00000004  /* Huge Frame Enable                 */
#define MAC2_DLY_CRC        0x00000008  /* Delayed CRC Mode                  */
#define MAC2_CRC_EN         0x00000010  /* Append CRC to every Frame         */
#define MAC2_PAD_EN         0x00000020  /* Pad all Short Frames              */
#define MAC2_VLAN_PAD_EN    0x00000040  /* VLAN Pad Enable                   */
#define MAC2_ADET_PAD_EN    0x00000080  /* Auto Detect Pad Enable            */
#define MAC2_PPREAM_ENF     0x00000100  /* Pure Preamble Enforcement         */
#define MAC2_LPREAM_ENF     0x00000200  /* Long Preamble Enforcement         */
#define MAC2_NO_BACKOFF     0x00001000  /* No Backoff Algorithm              */
#define MAC2_BACK_PRESSURE  0x00002000  /* Backoff Presurre / No Backoff     */
#define MAC2_EXCESS_DEF     0x00004000  /* Excess Defer                      */

/* Back-to-Back Inter-Packet-Gap Register */
#define IPGT_FULL_DUP       0x00000015  /* Recommended value for Full Duplex */
#define IPGT_HALF_DUP       0x00000012  /* Recommended value for Half Duplex */

/* Non Back-to-Back Inter-Packet-Gap Register */
#define IPGR_DEF            0x00000012  /* Recommended value                 */

/* Collision Window/Retry Register */
#define CLRT_DEF            0x0000370F  /* Default value                     */

/* PHY Support Register */
#define SUPP_SPEED          0x00000100  /* Reduced MII Logic Current Speed   */

/* Test Register */
#define TEST_SHCUT_PQUANTA  0x00000001  /* Shortcut Pause Quanta             */
#define TEST_TST_PAUSE      0x00000002  /* Test Pause                        */
#define TEST_TST_BACKP      0x00000004  /* Test Back Pressure                */

/* MII Management Configuration Register */
#define MCFG_SCAN_INC       0x00000001  /* Scan Increment PHY Address        */
#define MCFG_SUPP_PREAM     0x00000002  /* Suppress Preamble                 */
#define MCFG_CLK_SEL        0x0000001C  /* Clock Select Mask                 */
#define MCFG_RES_MII        0x00008000  /* Reset MII Management Hardware     */

#define MCFG_CLK_DIV28      0x0000001C  /* MDC = hclk / 28 */
#define MCFG_CLK_DIV36      0x00000020
#define MCFG_CLK_DIV64		0x0000003c

/* MII Management Command Register */
#define MCMD_READ           0x00000001  /* MII Read                          */
#define MCMD_SCAN           0x00000002  /* MII Scan continuously             */

#define MII_WR_TOUT         0x00050000  /* MII Write timeout count           */
#define MII_RD_TOUT         0x00050000  /* MII Read timeout count            */

/* MII Management Address Register */
#define MADR_REG_ADR        0x0000001F  /* MII Register Address Mask         */
#define MADR_PHY_ADR        0x00001F00  /* PHY Address Mask                  */

/* MII Management Indicators Register */
#define MIND_BUSY           0x00000001  /* MII is Busy                       */
#define MIND_SCAN           0x00000002  /* MII Scanning in Progress          */
#define MIND_NOT_VAL        0x00000004  /* MII Read Data not valid           */
#define MIND_MII_LINK_FAIL  0x00000008  /* MII Link Failed                   */

/* Command Register */
#define CR_RX_EN            0x00000001  /* Enable Receive                    */
#define CR_TX_EN            0x00000002  /* Enable Transmit                   */
#define CR_REG_RES          0x00000008  /* Reset Host Registers              */
#define CR_TX_RES           0x00000010  /* Reset Transmit Datapath           */
#define CR_RX_RES           0x00000020  /* Reset Receive Datapath            */
#define CR_PASS_RUNT_FRM    0x00000040  /* Pass Runt Frames                  */
#define CR_PASS_RX_FILT     0x00000080  /* Pass RX Filter                    */
#define CR_TX_FLOW_CTRL     0x00000100  /* TX Flow Control                   */
#define CR_RMII             0x00000200  /* Reduced MII Interface             */
#define CR_FULL_DUP         0x00000400  /* Full Duplex                       */

/* Status Register */
#define SR_RX_EN            0x00000001  /* Enable Receive                    */
#define SR_TX_EN            0x00000002  /* Enable Transmit                   */

/* Transmit Status Vector 0 Register */
#define TSV0_CRC_ERR        0x00000001  /* CRC error                         */
#define TSV0_LEN_CHKERR     0x00000002  /* Length Check Error                */
#define TSV0_LEN_OUTRNG     0x00000004  /* Length Out of Range               */
#define TSV0_DONE           0x00000008  /* Tramsmission Completed            */
#define TSV0_MCAST          0x00000010  /* Multicast Destination             */
#define TSV0_BCAST          0x00000020  /* Broadcast Destination             */
#define TSV0_PKT_DEFER      0x00000040  /* Packet Deferred                   */
#define TSV0_EXC_DEFER      0x00000080  /* Excessive Packet Deferral         */
#define TSV0_EXC_COLL       0x00000100  /* Excessive Collision               */
#define TSV0_LATE_COLL      0x00000200  /* Late Collision Occured            */
#define TSV0_GIANT          0x00000400  /* Giant Frame                       */
#define TSV0_UNDERRUN       0x00000800  /* Buffer Underrun                   */
#define TSV0_BYTES          0x0FFFF000  /* Total Bytes Transferred           */
#define TSV0_CTRL_FRAME     0x10000000  /* Control Frame                     */
#define TSV0_PAUSE          0x20000000  /* Pause Frame                       */
#define TSV0_BACK_PRESS     0x40000000  /* Backpressure Method Applied       */
#define TSV0_VLAN           0x80000000  /* VLAN Frame                        */

/* Transmit Status Vector 1 Register */
#define TSV1_BYTE_CNT       0x0000FFFF  /* Transmit Byte Count               */
#define TSV1_COLL_CNT       0x000F0000  /* Transmit Collision Count          */

/* Receive Status Vector Register */
#define RSV_BYTE_CNT        0x0000FFFF  /* Receive Byte Count                */
#define RSV_PKT_IGNORED     0x00010000  /* Packet Previously Ignored         */
#define RSV_RXDV_SEEN       0x00020000  /* RXDV Event Previously Seen        */
#define RSV_CARR_SEEN       0x00040000  /* Carrier Event Previously Seen     */
#define RSV_REC_CODEV       0x00080000  /* Receive Code Violation            */
#define RSV_CRC_ERR         0x00100000  /* CRC Error                         */
#define RSV_LEN_CHKERR      0x00200000  /* Length Check Error                */
#define RSV_LEN_OUTRNG      0x00400000  /* Length Out of Range               */
#define RSV_REC_OK          0x00800000  /* Frame Received OK                 */
#define RSV_MCAST           0x01000000  /* Multicast Frame                   */
#define RSV_BCAST           0x02000000  /* Broadcast Frame                   */
#define RSV_DRIB_NIBB       0x04000000  /* Dribble Nibble                    */
#define RSV_CTRL_FRAME      0x08000000  /* Control Frame                     */
#define RSV_PAUSE           0x10000000  /* Pause Frame                       */
#define RSV_UNSUPP_OPC      0x20000000  /* Unsupported Opcode                */
#define RSV_VLAN            0x40000000  /* VLAN Frame                        */

/* Flow Control Counter Register */
#define FCC_MIRR_CNT        0x0000FFFF  /* Mirror Counter                    */
#define FCC_PAUSE_TIM       0xFFFF0000  /* Pause Timer                       */

/* Flow Control Status Register */
#define FCS_MIRR_CNT        0x0000FFFF  /* Mirror Counter Current            */

/* Receive Filter Control Register */
#define RFC_UCAST_EN        0x00000001  /* Accept Unicast Frames Enable      */
#define RFC_BCAST_EN        0x00000002  /* Accept Broadcast Frames Enable    */
#define RFC_MCAST_EN        0x00000004  /* Accept Multicast Frames Enable    */
#define RFC_UCAST_HASH_EN   0x00000008  /* Accept Unicast Hash Filter Frames */
#define RFC_MCAST_HASH_EN   0x00000010  /* Accept Multicast Hash Filter Fram.*/
#define RFC_PERFECT_EN      0x00000020  /* Accept Perfect Match Enable       */
#define RFC_MAGP_WOL_EN     0x00001000  /* Magic Packet Filter WoL Enable    */
#define RFC_PFILT_WOL_EN    0x00002000  /* Perfect Filter WoL Enable         */

/* Receive Filter WoL Status/Clear Registers */
#define WOL_UCAST           0x00000001  /* Unicast Frame caused WoL          */
#define WOL_BCAST           0x00000002  /* Broadcast Frame caused WoL        */
#define WOL_MCAST           0x00000004  /* Multicast Frame caused WoL        */
#define WOL_UCAST_HASH      0x00000008  /* Unicast Hash Filter Frame WoL     */
#define WOL_MCAST_HASH      0x00000010  /* Multicast Hash Filter Frame WoL   */
#define WOL_PERFECT         0x00000020  /* Perfect Filter WoL                */
#define WOL_RX_FILTER       0x00000080  /* RX Filter caused WoL              */
#define WOL_MAG_PACKET      0x00000100  /* Magic Packet Filter caused WoL    */

/* Interrupt Status/Enable/Clear/Set Registers */
#define INT_RX_OVERRUN      0x00000001  /* Overrun Error in RX Queue         */
#define INT_RX_ERR          0x00000002  /* Receive Error                     */
#define INT_RX_FIN          0x00000004  /* RX Finished Process Descriptors   */
#define INT_RX_DONE         0x00000008  /* Receive Done                      */
#define INT_TX_UNDERRUN     0x00000010  /* Transmit Underrun                 */
#define INT_TX_ERR          0x00000020  /* Transmit Error                    */
#define INT_TX_FIN          0x00000040  /* TX Finished Process Descriptors   */
#define INT_TX_DONE         0x00000080  /* Transmit Done                     */
#define INT_SOFT_INT        0x00001000  /* Software Triggered Interrupt      */
#define INT_WAKEUP          0x00002000  /* Wakeup Event Interrupt            */

/* Power Down Register */
#define PD_POWER_DOWN       0x80000000  /* Power Down MAC                    */

/* RX Descriptor Control Word */
#define RCTRL_SIZE          0x000007FF  /* Buffer size mask                  */
#define RCTRL_INT           0x80000000  /* Generate RxDone Interrupt         */

/* RX Status Hash CRC Word */
#define RHASH_SA            0x000001FF  /* Hash CRC for Source Address       */
#define RHASH_DA            0x001FF000  /* Hash CRC for Destination Address  */

/* RX Status Information Word */
#define RINFO_SIZE          0x000007FF  /* Data size in bytes                */
#define RINFO_CTRL_FRAME    0x00040000  /* Control Frame                     */
#define RINFO_VLAN          0x00080000  /* VLAN Frame                        */
#define RINFO_FAIL_FILT     0x00100000  /* RX Filter Failed                  */
#define RINFO_MCAST         0x00200000  /* Multicast Frame                   */
#define RINFO_BCAST         0x00400000  /* Broadcast Frame                   */
#define RINFO_CRC_ERR       0x00800000  /* CRC Error in Frame                */
#define RINFO_SYM_ERR       0x01000000  /* Symbol Error from PHY             */
#define RINFO_LEN_ERR       0x02000000  /* Length Error                      */
#define RINFO_RANGE_ERR     0x04000000  /* Range Error (exceeded max. size)  */
#define RINFO_ALIGN_ERR     0x08000000  /* Alignment Error                   */
#define RINFO_OVERRUN       0x10000000  /* Receive overrun                   */
#define RINFO_NO_DESCR      0x20000000  /* No new Descriptor available       */
#define RINFO_LAST_FLAG     0x40000000  /* Last Fragment in Frame            */
#define RINFO_ERR           0x80000000  /* Error Occured (OR of all errors)  */

#define RINFO_ERR_MASK     (RINFO_FAIL_FILT | RINFO_CRC_ERR   | RINFO_SYM_ERR | \
                            RINFO_LEN_ERR   | RINFO_ALIGN_ERR | RINFO_OVERRUN)

/* TX Descriptor Control Word */
#define TCTRL_SIZE          0x000007FF  /* Size of data buffer in bytes      */
#define TCTRL_OVERRIDE      0x04000000  /* Override Default MAC Registers    */
#define TCTRL_HUGE          0x08000000  /* Enable Huge Frame                 */
#define TCTRL_PAD           0x10000000  /* Pad short Frames to 64 bytes      */
#define TCTRL_CRC           0x20000000  /* Append a hardware CRC to Frame    */
#define TCTRL_LAST          0x40000000  /* Last Descriptor for TX Frame      */
#define TCTRL_INT           0x80000000  /* Generate TxDone Interrupt         */

/* TX Status Information Word */
#define TINFO_COL_CNT       0x01E00000  /* Collision Count                   */
#define TINFO_DEFER         0x02000000  /* Packet Deferred (not an error)    */
#define TINFO_EXCESS_DEF    0x04000000  /* Excessive Deferral                */
#define TINFO_EXCESS_COL    0x08000000  /* Excessive Collision               */
#define TINFO_LATE_COL      0x10000000  /* Late Collision Occured            */
#define TINFO_UNDERRUN      0x20000000  /* Transmit Underrun                 */
#define TINFO_NO_DESCR      0x40000000  /* No new Descriptor available       */
#define TINFO_ERR           0x80000000  /* Error Occured (OR of all errors)  */

/* ENET Device Revision ID */
#define OLD_EMAC_MODULE_ID  0x39022000  /* Rev. ID for first rev '-'         */

/* DP83848C PHY Registers */
#define PHY_REG_BMCR        0x00        /* Basic Mode Control Register       */
#define PHY_REG_BMSR        0x01        /* Basic Mode Status Register        */
#define PHY_REG_IDR1        0x02        /* PHY Identifier 1                  */
#define PHY_REG_IDR2        0x03        /* PHY Identifier 2                  */
#define PHY_REG_ANAR        0x04        /* Auto-Negotiation Advertisement    */
#define PHY_REG_ANLPAR      0x05        /* Auto-Neg. Link Partner Abitily    */
#define PHY_REG_ANER        0x06        /* Auto-Neg. Expansion Register      */
#define PHY_REG_ANNPTR      0x07        /* Auto-Neg. Next Page TX            */

/* PHY Extended Registers */
#define PHY_REG_STS         0x10        /* Status Register                   */
#define PHY_REG_MICR        0x11        /* MII Interrupt Control Register    */
#define PHY_REG_MISR        0x12        /* MII Interrupt Status Register     */
#define PHY_REG_FCSCR       0x14        /* False Carrier Sense Counter       */
#define PHY_REG_RECR        0x15        /* Receive Error Counter             */
#define PHY_REG_PCSR        0x16        /* PCS Sublayer Config. and Status   */
#define PHY_REG_RBR         0x17        /* RMII and Bypass Register          */
#define PHY_REG_LEDCR       0x18        /* LED Direct Control Register       */
#define PHY_REG_PHYCR       0x19        /* PHY Control Register              */
#define PHY_REG_10BTSCR     0x1A        /* 10Base-T Status/Control Register  */
#define PHY_REG_CDCTRL1     0x1B        /* CD Test Control and BIST Extens.  */
#define PHY_REG_EDCR        0x1D        /* Energy Detect Control Register    */

#define PHY_FULLD_100M      0x2100      /* Full Duplex 100Mbit               */
#define PHY_HALFD_100M      0x2000      /* Half Duplex 100Mbit               */
#define PHY_FULLD_10M       0x0100      /* Full Duplex 10Mbit                */
#define PHY_HALFD_10M       0x0000      /* Half Duplex 10MBit                */
#define PHY_AUTO_NEG        0x3000      /* Select Auto Negotiation           */

#define DP83848C_DEF_ADR    0x0100      /* Default PHY device address        */
#define DP83848C_ID         0x20005C90  /* PHY Identifier                    */

// Ethernet power/clock control bit in PCONP register
#define PCENET 0x40000000
// Ethernet configuration for PINSEL2, as per user guide section 5.3
#define ENET_PINSEL2_CONFIG 0x50150105
// Ethernet configuration for PINSEL3, as per user guide section 5.4
#define ENET_PINSEL3_CONFIG 0x00000005
// Only bottom byte of PINSEL3 relevant to Ethernet
#define ENET_PINSEL3_MASK 0x0000000F


/*************************************************
 * CodeRed - PHY definitions for RDB1768 rev 2
 * which uses SMSC LAN8720 PHY instead of DP83848C
 *************************************************/
#define LAN8720_ID          0x0007C0F0  /* PHY Identifier                    */


void init_eth_mac(unsigned char *tx_double_buf, int double_len_tx, unsigned char *rx_double_buf,
                  int double_len_rx);
bool if_frame_rec(void);

// power off the Ethernet module. Useful on LPC1769 board to remove glitches on power supply
void ethernet_power_down(void);


#endif

